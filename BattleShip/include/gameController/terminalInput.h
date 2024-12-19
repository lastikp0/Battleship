#ifndef TERMINAL_INPUT
#define TERMINAL_INPUT

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>

#include "fileManager.h"

class TerminalInput {
public:
    TerminalInput();

    Coords getCoords();
    int getNumber();
    std::vector<int> getVectorFromMap();
    ShipOrientation getOrientation();
    bool getYN();

    std::string getCommand();
    std::map<char, std::string>& getCommandMap();

    void getAnything();

private:
    void loadCommands(const std::string file);

    std::map<char, std::string> command_map_;

    std::vector<std::string> commands_ = {"attack", "ability", "save", "load", "exit", "help", "new"};
};

#endif