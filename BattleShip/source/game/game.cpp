#include "game.h"

#include "shipManager.h"
#include "field.h"
#include "abilityManager.h"

#include "participant.h"
#include "bot.h"
#include "player.h"

#include <vector>
#include <stdexcept>
#include <ctime>

#include "debug_CLI.h"

Game::Game()
{
    game_state_.current_participant_index_ = 0;
    game_state_.round_count_ = 0;
    game_state_.move_count_ = 0;
}

Game::~Game()
{
    for (auto participant: game_state_.participants_) {
        delete participant;
    }    
    game_state_.participants_.clear();
}

void Game::createParticipants(int player_count, int bot_count)
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

    game_state_.participants_.clear();

    //debug mode
    player_count = 1;
    bot_count = 1;

    game_state_.player_count_ = player_count;
    game_state_.bot_count_ = bot_count;

    Participant* participant;

    int player_or_bot;
    while (player_count + bot_count > 0) {
        player_or_bot = rand() % 2;

        if (player_or_bot && bot_count) {
            bot_count--;
            participant = createBot();
        } else if (!player_or_bot && player_count){
            player_count--;
            participant = createPlayer();
        } else if ((player_or_bot && !bot_count) || (!player_or_bot && !player_count)) {
            continue;
        }
        game_state_.participants_.push_back(participant);
    }
}

void Game::start(int player_count, int bot_count)
{
    //debug message
    std::cout << "Creating participants\n";

    createParticipants(1, 1);

    //debug message
    std::cout << "Participants created\n";

    for (auto participant : game_state_.participants_) {
        participant->placeShips();
    }

    game_state_.status_ = GameStatus::active;
    gameCycle();
}

void Game::gameCycle()
{
    //debug message
    std::cout << "Game started\n";

    bool game_result = true;
    while (game_result) {
        roundCycle();
        game_result = isPlayerWinner();

        if (game_result) {
            restart();
        } else {
            char ch;
            std::cout << "Game over. Restart?(y or n): ";
            std::cin >> ch;
            if (ch == 'y') {
                restart();
                game_result = true;
            }
        }
    }

    //debug message
    std::cout << "Game ended\n";
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
                participant = createBot();
            } else if (!player_or_bot && player_count){
                player_count--;
                if (!winner_added) {
                    participant = winner;
                    winner_added = true;
                } else {
                    participant = createPlayer();
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

        createParticipants(game_state_.player_count_, game_state_.bot_count_);
    }

    game_state_.status_ = GameStatus::active;
    game_state_.current_participant_index_ = 0;
    game_state_.round_count_++;
    game_state_.move_count_ = 0;

    for (auto participant : game_state_.participants_) {
        participant->placeShips();
    }
}

void Game::runRound()
{
    if (getAliveParticipantCount() == 1) {
        game_state_.status_ = GameStatus::finished;
        return;
    }

    //debug messages
    std::cout << "Round " << game_state_.round_count_ << "\n";
    std::cout << "Move " << game_state_.move_count_ << "\n";

    int command = 0;
    Participant* participant = game_state_.participants_[game_state_.current_participant_index_];
    while (!participant->isAlive()) {
        game_state_.current_participant_index_ = (++game_state_.current_participant_index_) % getParticipantCount();
        participant = game_state_.participants_[game_state_.current_participant_index_];
    }

    //debug message
    std::cout << "Participant " << game_state_.current_participant_index_ << "(";

    int target_index = (game_state_.current_participant_index_ + 1) % getParticipantCount();
    while (!game_state_.participants_[target_index]->isAlive()) {
        target_index = (++target_index) % getParticipantCount();
    }

    auto player = dynamic_cast<Player*>(participant);
    if (player) {
        //debug message
        std::cout << "player) move\n";

        command = getCommand();

    } else {
        //debug message
        std::cout << "bot) move\n";
    }

    if (command == 0) {
        //debug message
        std::cout << "Attack\n";

        bool attack_result;
        attack_result = participant->attackCell(game_state_.participants_[target_index]);

        if (attack_result && player) {
            player->addAbility();
        }

    } else if (command == 1) {
        //debug message
        std::cout << "Ability\n";

        player->castAbility(game_state_.participants_[target_index]);

    } else if (command == 2) {
        std::cout << "Saving\n";

        file_manager = new FileManager("save.txt");
        file_manager->write(game_state_);
        delete file_manager;

        return;

    } else if (command == 3) {
        std::cout << "Loading (none)\n";

        file_manager = new FileManager("save.txt", false);
        file_manager->read(game_state_);
        delete file_manager;

        return;

    } else {
        throw std::invalid_argument("Command doesn't exist");
    }

    if (getAliveParticipantCount() != 1) {
        game_state_.current_participant_index_ = (++game_state_.current_participant_index_) % getParticipantCount();
        game_state_.move_count_++;
    }
}

void Game::roundCycle()
{
    //debug message
    std::cout << "Round started\n";

    while (getGameStatus() != GameStatus::finished) {
        runRound();
    }

    //debug message
    std::cout << "Round ended\n";
}

GameStatus Game::getGameStatus() const noexcept
{
    return game_state_.status_;
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

Participant* Game::createPlayer()
{
    PlayerStats* player_stats = getPlayerStats();

    Participant* player = new Player(player_stats->field_size, player_stats->ship_sizes);
    delete player_stats;

    return player;
}

Participant* Game::createBot()
{
    // Coords field_size = {5, 5};
    // std::vector<int> ship_sizes = {1, 2, 3, 4};

    Coords field_size = {3, 3};
    std::vector<int> ship_sizes = {1};

    Participant* bot = new Bot(field_size, ship_sizes);
    return bot;
}