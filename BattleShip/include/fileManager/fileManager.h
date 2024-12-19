#ifndef FILE_MANAGER
#define FILE_MANAGER

#include "gameState.h"

#include <fstream>
#include <string>
#include <sstream>

class FileManager
{
public:
    FileManager(std::string file = "save.txt", bool write_mode = true);
    ~FileManager();

    void write(GameState& state);
    void read(GameState& state);

    void getData(std::string& str);

private:
    std::ifstream in;
    std::ofstream out;
};

#endif