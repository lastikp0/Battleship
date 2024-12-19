#include "gameState.h"

#include "shipManager.h"
#include "field.h"
#include "abilityManager.h"

#include "participant.h"
#include "bot.h"
#include "player.h"

#include "hasher.h"

#include <vector>
#include <fstream>
#include <sstream>

std::ifstream& operator>>(std::ifstream& in, GameState& state) 
{
    int hash1;
    int hash2;

    std::stringstream ss;
    std::string data;

    bool check_res;

    in >> hash1;
    in >> hash2;
        
    in.get();
    ss << in.rdbuf();
    data = ss.str();
    Hasher hasher(data);

    if (hash1 == hasher.hash1 && hash2 == hasher.hash2) {
        check_res = true;
    } else {
        check_res = false;
    }

    if (!check_res) {
        return in;
    }

    state.load_ = true;

    int status;
    ss >> status;
    if (status == 0) {
        state.status_ = GameStatus::active;
    } else {
        state.status_ = GameStatus::finished;
    }

    ss >> state.current_participant_index_;
    ss >> state.round_count_;
    ss >> state.move_count_;

    ss >> state.player_count_;
    ss >> state.bot_count_;

    for (int i = 0; i < state.participants_.size(); i++) {
        delete state.participants_[i];
    }
    state.participants_.clear();

    for (int i = 0; i < state.player_count_ + state.bot_count_; i++) {
        int player_or_bot;

        //AbilityManager
        AbilityManager* ability_manager = nullptr;

        ss >> player_or_bot;
        if (player_or_bot == 0) {
            int abilities_count;
            ss >> abilities_count;

            std::vector<int> abilities_info(abilities_count);

            for (int i = 0; i < abilities_count; i++) {
                ss >> abilities_info[i];
            }

            ability_manager = new AbilityManager();

            ability_manager->setAbilities(abilities_info);
        }

        //Field
        int size_x, size_y;
        ss >> size_x >> size_y;

        Field* field = new Field(size_x, size_y);

        std::vector<std::vector<char>> field_info;
        field_info.resize(size_y);
        for (int y = 0; y < size_y; y++) {
            field_info[y].resize(size_x);

            for (int x = 0; x < size_x; x++) {
                ss >> field_info[y][x];
            }
        }

        field->setField(field_info);

        //Ships
        int ship_count;
        ss >> ship_count;

        std::vector<ShipInfo> ship_info(ship_count);

        ShipManager* ship_manager = new ShipManager();

        for (int i = 0; i < ship_count; i++) {
            ss >> ship_info[i].x >> ship_info[i].y >> ship_info[i].orientation >> ship_info[i].size;

            ship_info[i].segments_health.clear();
            ship_info[i].segments_health.resize(ship_info[i].size);
            for (int j = 0; j < ship_info[i].size; j++) {
                ss >> ship_info[i].segments_health[j];
            }
        }

        for (int i = 0; i < ship_count; i++) {
            Ship* ship = new Ship(ship_info[i].size);
            ship_manager->addShip(ship);

            for (int j = 0; j < ship_info[i].size; j++) {
                ship->setSegmentHealth(j, ship_info[i].segments_health[j]);
            }

            if (ship_info[i].orientation == 0) {
                field->placeShip(ship, {ship_info[i].x, ship_info[i].y}, ShipOrientation::horizontal);
            } else {
                field->placeShip(ship, {ship_info[i].x, ship_info[i].y}, ShipOrientation::vertical);
            }
            ship_manager->makeShipUsed(0);
        }

        Participant* participant;
        if (player_or_bot == 0) {
            participant = new Player();
        } else {
            participant = new Bot();
        }
        participant->field = field;
        participant->ship_manager = ship_manager;
        participant->ability_manager = ability_manager;

        state.participants_.push_back(participant);
    }

    return in;
}

std::ofstream& operator<<(std::ofstream& out, GameState& state) 
{
    std::string data = "";

    if (state.status_ == GameStatus::active) {
        data += "0\n";
    } else {
        data += "1\n";
    }

    data += std::to_string(state.current_participant_index_) + " ";
    data += std::to_string(state.round_count_) + " ";
    data += std::to_string(state.move_count_) + "\n";

    data += std::to_string(state.player_count_) + " ";
    data += std::to_string(state.bot_count_) + "\n";

    for (int i = 0; i < state.participants_.size(); i++) {
        Participant* participant = state.participants_[i];
        if (participant->isBot()) {
            data += "1\n";
        } else {
            data += "0\n";
            data += participant->ability_manager->getAllAbilities();
        }

        data += participant->field->getField() + participant->field->getShips();
    }

    Hasher hasher(data);

    out << hasher.hash1 << "\n";
    out << hasher.hash2 << "\n";

    out << data;

    state.save_ = true;

    return out;
}