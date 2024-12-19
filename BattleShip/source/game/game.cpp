#include "game.h"

#include "gameState.h"
#include "fileManager.h"

#include <vector>
#include <stdexcept>

Game::Game()
{
    game_state_.participants_.clear();
}

Game::~Game()
{
    for (auto participant: game_state_.participants_) {
        delete participant;
    }    
    game_state_.participants_.clear();
}

void Game::setParticipantsCount(int player_count, int bot_count)
{
    if (player_count < 0) {
        throw std::invalid_argument("Players count can't be negative");
    }
    if (bot_count < 0) {
        throw std::invalid_argument("Bots count can't be negative");
    }
    if (player_count + bot_count < 2) {
        throw std::logic_error("Participants count must be greater than 1");
    }

    game_state_.player_count_ = player_count;
    game_state_.bot_count_ = bot_count;
}

void Game::start()
{
    game_state_.current_participant_index_ = 0;
    game_state_.round_count_ = 0;
    game_state_.move_count_ = 0;

    createParticipants();

    game_state_.status_ = GameStatus::active;
}

void Game::restart()
{
    if (isPlayerWinner()) {
        Participant* winner = game_state_.participants_[game_state_.current_participant_index_];

        for (int i = 0; i < game_state_.participants_.size(); i++) {
            if (i != game_state_.current_participant_index_) {
                delete game_state_.participants_[i];
            }
        }

        game_state_.participants_.clear();

        int player_count = game_state_.player_count_;
        bool winner_added = false;

        int bot_count = game_state_.bot_count_;
        int index = 0;

        Participant* participant;
        int player_or_bot;
        while (player_count + bot_count > 0) {
            player_or_bot = rand() % 2;

            if (player_or_bot && bot_count) {
                bot_count--;
                participant = new Bot();
            } else if (!player_or_bot && player_count){
                player_count--;
                if (!winner_added) {
                    participant = winner;
                    winner_added = true;
                } else {
                    participant = new Player();
                }
            } else if ((player_or_bot && !bot_count) || (!player_or_bot && !player_count)) {
                continue;
            }

            if (index == game_state_.current_participant_index_) {
                index++;
            }

            game_state_.participants_.push_back(participant);
            index++;
        }
    } else {
        for (int i = 0; i < game_state_.participants_.size(); i++) {
            delete game_state_.participants_[i];
        }

        createParticipants();
    }

    game_state_.status_ = GameStatus::active;
    game_state_.current_participant_index_ = 0;
    game_state_.round_count_++;
    game_state_.move_count_ = 0;
}

void Game::createParticipants()
{
    game_state_.participants_.clear();

    Participant* participant;
    int player_count = game_state_.player_count_;
    int bot_count = game_state_.bot_count_;

    int player_or_bot;
    while (player_count + bot_count > 0) {
        player_or_bot = rand() % 2;

        if (player_or_bot && bot_count) {
            bot_count--;
            participant = new Bot();
        } else if (!player_or_bot && player_count){
            player_count--;
            participant = new Player();
        } else if ((player_or_bot && !bot_count) || (!player_or_bot && !player_count)) {
            continue;
        }

        game_state_.participants_.push_back(participant);
    }
}

void Game::initBot(Participant* participant, Coords field_size, std::vector<int> ship_sizes)
{
    participant->field = new Field(field_size.x, field_size.y);
    participant->ship_manager = new ShipManager(ship_sizes);
    participant->ability_manager = nullptr;
}

void Game::initPlayer(Participant* participant, Coords field_size, std::vector<int> ship_sizes)
{
    initBot(participant, field_size, ship_sizes);
    participant->ability_manager = new AbilityManager();
}

void Game::placeShip(Participant* participant, int index, Coords coords, ShipOrientation orientation)
{
    participant->placeShip(index, coords, orientation);
}

void Game::setTarget(int index)
{
    if (index < 0) {
        target_index_ = 0;
    } else if (index >= getParticipantCount()) {
        target_index_ = getParticipantCount() - 1;
    } else {
        target_index_ = index;
    }

    if (target_index_ == game_state_.current_participant_index_) {
        target_index_ = (++target_index_) % getParticipantCount();
    }
    while (!game_state_.participants_[target_index_]->isAlive()) {
        target_index_ = (++target_index_) % getParticipantCount();
    }
}

void Game::attack(Coords coords)
{
    Participant* participant = game_state_.participants_[game_state_.current_participant_index_];
    bool attack_result;
    attack_result = participant->attackCell(game_state_.participants_[target_index_], coords);

    if (attack_result && !participant->isBot()) {
        if (participant->ability_manager != nullptr) {
            participant->ability_manager->addAbility();
        }
    }

    game_state_.save_ = false;

    if (getAliveParticipantCount() != 1) {
        game_state_.current_participant_index_ = (++game_state_.current_participant_index_) % getParticipantCount();
        game_state_.move_count_++;
    } else {
        game_state_.status_ = GameStatus::finished;
    }
}

void Game::ability(IAbilitySettings* settings)
{
    Participant* participant = game_state_.participants_[game_state_.current_participant_index_];
    participant->ability_manager->castAbility(settings);

    game_state_.save_ = false;

    if (getAliveParticipantCount() != 1) {
        game_state_.current_participant_index_ = (++game_state_.current_participant_index_) % getParticipantCount();
        game_state_.move_count_++;
    } else {
        game_state_.status_ = GameStatus::finished;
    }
}

void Game::save(std::string& file)
{
    file_manager = new FileManager(file);
    file_manager->write(game_state_);
    delete file_manager;

    return;
}

bool Game::isSaved()
{
    return game_state_.save_;
}

bool Game::load(std::string& file)
{
    file_manager = new FileManager(file, false);
    file_manager->read(game_state_);
    delete file_manager;

    if (game_state_.load_) {
        game_state_.save_ = true;
    }

    return game_state_.load_;
}

GameStatus Game::getGameStatus() const noexcept
{
    return game_state_.status_;
}

Coords Game::getRoundMove() const noexcept
{
    return {game_state_.round_count_, game_state_.move_count_};
}

int Game::getParticipantCount() const noexcept
{
    return game_state_.participants_.size();
}

int Game::getAliveParticipantCount() const noexcept
{
    int count = 0;
    for (auto participant : game_state_.participants_) {
        if (participant->isAlive()) {
            count++;
        }
    }
    return count;
}

int Game::getCurrentIndex() noexcept
{
    Participant* participant = game_state_.participants_[game_state_.current_participant_index_];
    while (!participant->isAlive()) {
        game_state_.current_participant_index_ = (++game_state_.current_participant_index_) % getParticipantCount();
        participant = game_state_.participants_[game_state_.current_participant_index_];
    }

    return game_state_.current_participant_index_;
}

int Game::getTargetIndex() noexcept
{
    return target_index_;
}

Participant* Game::getParticipant(int index) const
{
    if (index < 0 || index >= game_state_.participants_.size()) {
        throw std::out_of_range("Participant index out of range");
    }

    return game_state_.participants_[index];
}

bool Game::isPlayerWinner() const noexcept
{
    if (game_state_.status_ == GameStatus::finished) {
        auto player = dynamic_cast<Player*>(game_state_.participants_[game_state_.current_participant_index_]);
        if (player) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}