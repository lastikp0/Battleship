#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <iostream>
#include <map>
#include <functional>
#include "gameRenderer.h"
#include "game.h"

template<typename Input, typename Output>
class GameController {
public:
    GameController(Game& game):
        game_(game),
        renderer_(game)
    {
        initializeCommands();
    }
    
    void start()
    {
        command_map_ = input_.getCommandMap();
        for (auto [key, value]: command_map_) {
            key_map_[value] = key;
        }

        renderer_.setHelp(command_map_);

        while (true) {
            std::string message = std::string("New game [") + key_map_["new"]
            + std::string("], load save[") + key_map_["load"]
            + std::string("], help[") + key_map_["help"]
            + std::string("] or exit[") + key_map_["exit"]
            + std::string("]?");

            renderer_.render(message);

            std::string option = input_.getCommand();
            if (option != "new" && option != "load" && option != "help" && option != "exit") {
                renderer_.render("Option unavaliable. Try again");
            } else {
                commands_[option]();
            }
        }
    }

private:
    std::string file = "save.txt";

    Game& game_;
    bool game_started_ = false;

    Input input_;
    GameRenderer<Output> renderer_;

    std::map<std::string, std::function<void()>> commands_;
    std::map<char, std::string> command_map_;
    std::map<std::string, char> key_map_;

    void startGame()
    {
        game_.setParticipantsCount(1, 1);
        game_.createParticipants();
        game_.start();

        for (int i = 0; i < game_.getParticipantCount(); i++) {
            Participant* participant = game_.getParticipant(i);
            if (participant->ready()) {
                continue;
            }
            if (participant->isBot()) {
                //main
                game_.initBot(participant, {10, 10}, {1, 2, 3, 4});

                //debug
                // game_.initBot(participant, {2, 2}, {1});

                while (!(participant->ready())) {
                    Coords coords;

                    //main
                    coords.x = rand() % 10;
                    coords.y = rand() % 10;

                    //debug
                    // coords.x = 0;
                    // coords.y = 0;

                    int orientation = rand() % 2;

                    try
                    {
                        if (orientation) {
                            game_.placeShip(participant, 0, coords, ShipOrientation::vertical);
                        } else {
                            game_.placeShip(participant, 0, coords, ShipOrientation::horizontal);
                        }
                    }
                    catch(const std::out_of_range& e)
                    {
                        continue;
                    }
                    catch(const ShipPlacementException& e)
                    {
                        continue;
                    }
                }

            } else {
                //main
                game_.initPlayer(participant, {10, 10}, {1, 2, 3, 4});

                //debug
                // game_.initPlayer(participant, {2, 2}, {1});

                while (!(participant->ready())) {
                    renderer_.render("draw_participants");

                    renderer_.render("Select ship from unused [index]");
                    int index = input_.getNumber();

                    renderer_.render("Input coordinates (x y)");
                    Coords coords = input_.getCoords();

                    renderer_.render("Input orientation [h/v]");
                    ShipOrientation orientation = input_.getOrientation();

                    try
                    {
                        game_.placeShip(participant, index, coords, orientation);
                    }
                    catch(const std::out_of_range& e)
                    {
                        renderer_.render(e.what());
                        continue;
                    }
                    catch(const ShipPlacementException& e)
                    {
                        renderer_.render(e.what());
                        continue;
                    }
                }

                renderer_.render("draw_participants");
            }
        }
    }

    void restartGame()
    {
        game_.restart();

        for (int i = 0; i < game_.getParticipantCount(); i++) {
            Participant* participant = game_.getParticipant(i);
            if (participant->ready()) {
                continue;
            }
            if (participant->isBot()) {
                //main
                game_.initBot(participant, {10, 10}, {1, 2, 3, 4});

                //debug
                // game_.initBot(participant, {2, 2}, {1});

                while (!(participant->ready())) {
                    Coords coords;

                    //main
                    coords.x = rand() % 10;
                    coords.y = rand() % 10;

                    //debug
                    // coords.x = 0;
                    // coords.y = 0;

                    int orientation = rand() % 2;

                    try
                    {
                        if (orientation) {
                            game_.placeShip(participant, 0, coords, ShipOrientation::vertical);
                        } else {
                            game_.placeShip(participant, 0, coords, ShipOrientation::horizontal);
                        }
                    }
                    catch(const std::out_of_range& e)
                    {
                        continue;
                    }
                    catch(const ShipPlacementException& e)
                    {
                        continue;
                    }
                }

            } else {
                //main
                game_.initPlayer(participant, {10, 10}, {1, 2, 3, 4});

                //debug
                // game_.initPlayer(participant, {2, 2}, {1});

                while (!(participant->ready())) {
                    renderer_.render("draw_participants");

                    renderer_.render("Select ship from unused [index]");
                    int index = input_.getNumber();

                    renderer_.render("Input coordinates (x y)");
                    Coords coords = input_.getCoords();

                    renderer_.render("Input orientation [h/v]");
                    ShipOrientation orientation = input_.getOrientation();

                    try
                    {
                        game_.placeShip(participant, index, coords, orientation);
                    }
                    catch(const std::out_of_range& e)
                    {
                        renderer_.render(e.what());
                        continue;
                    }
                    catch(const ShipPlacementException& e)
                    {
                        renderer_.render(e.what());
                        continue;
                    }
                }

                renderer_.render("draw_participants");
            }
        }
    }

    void initializeCommands()
    {
        commands_["attack"] = [&]()
        {
            renderer_.render("Attack");

            //current participant
            Participant* current = game_.getParticipant(game_.getCurrentIndex());

            if (current->isBot()) {
                while (true) {
                    Coords coords;

                    //main
                    coords.x = rand() % 10;
                    coords.y = rand() % 10;

                    //debug
                    // coords.x = 0;
                    // coords.y = 0;

                    try
                    {
                        game_.attack(coords);
                        break;
                    }
                    catch(const AttackOutOfRangeException& e)
                    {
                        continue;
                    }
                }
                
            } else {
                while (true) {
                    renderer_.render("draw_fields");

                    renderer_.render("Input coordinates (x y)");
                    Coords coords = input_.getCoords();

                    try
                    {
                        game_.attack(coords);
                        break;
                    }
                    catch(const AttackOutOfRangeException& e)
                    {
                        renderer_.render(e.what());
                        continue;
                    }
                }

                renderer_.render("draw_fields");
                renderer_.render("Press enter to continue");
                input_.getAnything();
            }
        };
        
        commands_["ability"] = [&]()
        {
            renderer_.render("Ability");

            Participant* current = game_.getParticipant(game_.getCurrentIndex());

            if (current->ability_manager->size() > 0) {
                AbilityType type = current->ability_manager->getAbility();

                if (type == AbilityType::DoubleDamage) {
                    renderer_.render("Double damage!");
                    renderer_.render("Next attack damage is doubled");

                    DoubleDamageSettings settings(current->damage);
                    game_.ability(&settings);

                } else if (type == AbilityType::Scanner) {
                    renderer_.render("Scanner!");
                    renderer_.render("Scan 2x2 area for ships");
                    renderer_.render("Input coordinates (x y)");

                    Coords coords = input_.getCoords();
                    bool scan_result;

                    Participant* target = game_.getParticipant(game_.getTargetIndex());

                    ScannerSettings settings(*(target->field), coords, scan_result);
                    game_.ability(&settings);

                    if (scan_result) {
                        renderer_.render("Ship found");
                    } else {
                        renderer_.render("No ship found");
                    }
                } else {
                    renderer_.render("Bombardment!");
                    renderer_.render("Garanteed hit (stacks with Double damage)");

                    Participant* target = game_.getParticipant(game_.getTargetIndex());

                    BombardmentSettings settings(*(target->field), current->damage);
                    game_.ability(&settings);
                    current->damage = 1;
                }

            } else {
                renderer_.render("No abilities avaliable");
            }
            
            renderer_.render("draw_fields");
            renderer_.render("Press enter to continue");
            input_.getAnything();
        };
        
        commands_["save"] = [&]()
        {
            renderer_.render("Save game? [y/n]");
            bool option = input_.getYN();

            if (!option) {
                return;
            }

            game_.save(file);
        };
        
        commands_["load"] = [&]()
        {
            renderer_.render("Load save? [y/n]");
            bool option = input_.getYN();

            if (!option) {
                return;
            }

            renderer_.render("Load save");

            bool load = false;
            bool error = false;
            try
            {
                load = game_.load(file);
            }
            catch(const std::exception& e)
            {
                error = true;
            }
                
            if (load) {
                renderer_.render("Save loaded");
            } else if (error) {
                renderer_.render("Failed to open save file");
            } else {
                renderer_.render("Save file corrupted");
            }

            if ((!load || error) && !game_started_) {
                while (true) {
                    std::string message = std::string("New game [") + key_map_["new"]
                    + std::string("] or exit[") + key_map_["exit"]
                    + std::string("]?");

                    renderer_.render(message);

                    std::string option = input_.getCommand();
                    if (option != "new" && option != "exit") {
                        renderer_.render("Option unavaliable. Try again");
                    } else {
                        commands_[option]();
                        break;
                    }
                }
            } else {
                if (game_started_) {
                    return;
                }

                game_started_ = true;
            }

            gameCycle();
        };
        
        commands_["exit"] = [&]()
        {
            renderer_.render("Exit? [y/n]");
            bool option = input_.getYN();

            if (!option) {
                return;
            }

            if (game_started_ && !(game_.isSaved())) {
                commands_["save"]();
            }

            renderer_.render("Exit");

            exit(0);
        };
        
        commands_["help"] = [&]()
        {
            renderer_.render("help");
            renderer_.render("Press enter to continue");
            input_.getAnything();
        };
        
        commands_["new"] = [&]()
        {
            if (game_started_) {
                renderer_.render("New game? [y/n]");
                bool option = input_.getYN();

                if (!option) {
                    return;
                }
            }

            renderer_.render("New game");
            game_started_ = true;

            startGame();
            gameCycle();
        };
    }

    void gameCycle()
    {
        bool game_result = true;
        while (game_result) {
            roundCycle();
            game_result = game_.isPlayerWinner();

            if (game_result) {
                restartGame();
            } else {
                renderer_.render("Game over");
                break;
            }
        }

        game_started_ = false;
    }

    void roundCycle()
    {
        while (game_.getGameStatus() != GameStatus::finished) {
            runRound();
        }
    }

    void runRound()
    {
        //round & move info
        int round, move;

        round = game_.getRoundMove().x;
        std::string message = "Round " + std::to_string(round) + "\n";

        move = game_.getRoundMove().y;
        message += "Move " + std::to_string(move);

        renderer_.render(message);

        renderer_.render("draw_fields");

        //set target (next)
        game_.setTarget(game_.getCurrentIndex());

        message = "Participant " + std::to_string(game_.getCurrentIndex()) + " move";
        renderer_.render(message);

        std::string option = "attack";

        //current participant
        Participant* current = game_.getParticipant(game_.getCurrentIndex());
        
        if (!(current->isBot())) {
            std::string message = std::string("Input command (for help type[") + key_map_["help"] + std::string("])");
            renderer_.render(message);

            option = input_.getCommand();
        }

        commands_[option]();
    }
};

#endif 