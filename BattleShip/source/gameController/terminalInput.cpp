#include "terminalInput.h"
#include "fileManager.h"

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>

TerminalInput::TerminalInput()
{
    loadCommands("commands.txt");
}

void TerminalInput::loadCommands(const std::string file) {
    FileManager* file_manager;
    bool success;

    std::string info;
    try
    {
        file_manager = new FileManager(file, false);
        success = true;
    }
    catch(const std::exception& e)
    {
        success = false;
    }

    if (success) {
        std::cout << "Loading command binds from file" << std::endl;

        file_manager->getData(info);
        delete file_manager;

        std::stringstream ss(info);

        info = "";
        for (int i = 0; i < commands_.size(); i++) {
            info += " ";
            if (!(ss >> info[i])) {
                std::cout << "Not all commands binded" << std::endl;
                success = false;
                break;
            }
        }

        std::set<char> info_set(info.begin(), info.end());
        if (info.size() != info_set.size()) {
            std::cout << "Some keys were binded to multiple commands" << std::endl;
            success = false;
        }
    }

    if (success) {
        for (int i = 0; i < commands_.size(); i++) {
            command_map_[info[i]] = commands_[i];
        }
        
        return;
    }

    std::cout << "Loading default command binds" << std::endl;

    command_map_ = {
        {'w', "attack"},
        {'q', "ability"},
        {'e', "save"},
        {'r', "load"},
        {'z', "exit"},
        {'h', "help"},
        {'n', "new"}
    };
}

Coords TerminalInput::getCoords()
{
    int x, y;
    std::string input;
    while (true) {
        if (std::getline(std::cin, input)) {
            std::istringstream iss(input);

            if (iss >> x >> y && iss.eof() && x >= 0 && y >= 0) {
                break;
            }
        }

        std::cout << "Invalid input. Please enter two non-negative integers.\n";
    }

    return {x, y};
}

int TerminalInput::getNumber()
{
    int n;
    std::string input;
    while (true) {
        if (std::getline(std::cin, input)) {
            std::istringstream iss(input);

            if (iss >> n && iss.eof()) {
                break;
            }
        }

        std::cout << "Invalid input. Please enter integer" << std::endl;
    }
    
    return n;
}

std::vector<int> TerminalInput::getVectorFromMap()
{
    std::map<int, int> map;
    for (int i = 1; i < 5; i++) {
        int num;
        std::string input;
        while (true) {
            if (std::getline(std::cin, input)) {
                std::istringstream iss(input);
                if (iss >> num && iss.eof() && num >= 0) {
                    map[i] = num;
                    break;
                }
            }

            std::cout << "Invalid input. Please enter a non-negative integer." << std::endl;
        }
    }

    std::vector<int> vec;
    vec.clear();
    for (auto [key, value]: map) {
        for (int i = 0; i < value; i++) {
            vec.push_back(key);
        }
    }
    
    return vec;
}

ShipOrientation TerminalInput::getOrientation()
{
    std::string input;
    while (true) {
        if (std::getline(std::cin, input)) {
            if (input.size() == 1) {
                char c = std::tolower(input[0]);
                if (c == 'v') {
                    return ShipOrientation::vertical;
                } else if (c == 'h') {
                    return ShipOrientation::horizontal;
                }
            }
        }

        std::cout << "Invalid input. Please enter vertical [v] or horizontal [h]" << std::endl;
    }
}

bool TerminalInput::getYN()
{
    std::string input;
    while (true) {
        if (std::getline(std::cin, input)) {
            if (input.size() == 1) {
                char c = std::tolower(input[0]);
                if (c == 'y') {
                    return true;
                } else if (c == 'n') {
                    return false;
                }
            }
        }

        std::cout << "Invalid input. Please enter vertical [v] or horizontal [h]" << std::endl;
    }
}

std::string TerminalInput::getCommand() {
    std::string input;
    while (true) {
        if (std::getline(std::cin, input)) {
            if (input.size() == 1) {
                char c = std::tolower(input[0]);
                if (command_map_.find(c) != command_map_.end()) {
                    return command_map_[c];
                }
            }
        }

        std::cout << "Invalid input" << std::endl;
        std::cout << "Avaliable commands:" << std::endl;
        for (auto [key, value]: command_map_) {
            std::cout << key << ": " << value << std::endl;
        }
    }
}

std::map<char, std::string>& TerminalInput::getCommandMap()
{
    return command_map_;
}

void TerminalInput::getAnything()
{
    std::string input;
    std::getline(std::cin, input);
    return;
}