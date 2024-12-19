#ifndef TERMINAL_OUTPUT
#define TERMINAL_OUTPUT

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "game.h"

class TerminalOutput {
public:
    void drawFields(Game& game);

    void drawParticipant(Game& game, int index);

    void drawMessage(std::string message);

    void drawHelp(std::map<char, std::string>& commands);
};

#endif