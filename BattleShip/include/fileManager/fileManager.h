#ifndef FILE_MANAGER
#define FILE_MANAGER

#include "gameState.h"

#include <fstream>
#include <string>

class FileManager
{
public:
    FileManager(std::string file = "save.txt", bool write_mode = true);
    ~FileManager();

    void write(GameState& state);
    void read(GameState& state);

private:
    std::ifstream in;
    std::ofstream out;
};

#endif