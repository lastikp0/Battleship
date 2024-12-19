#ifndef GAME_RENDER
#define GAME_RENDER

#include <iostream>
#include <string>
#include <map>
#include "game.h"

class Game;

template<typename Output>
class GameRenderer {
private:
    Output output_;
    Game& game_;
    std::map<char, std::string> command_map_;

public:
    GameRenderer(Game& game):
        game_(game)
    {}

    void setHelp(std::map<char, std::string>& command_map)
    {
        command_map_ = command_map;
    }

    void render(std::string command)
    {
        if (command == "draw_fields") {
            output_.drawFields(game_);
        } else if (command == "draw_participants") {
            for (int i = 0; i < game_.getParticipantCount(); i++) {
                output_.drawParticipant(game_, i);
            }
        } else if (command == "help") {
            output_.drawHelp(command_map_);
        } else {
            output_.drawMessage(command);
        }
    }
};

#endif 