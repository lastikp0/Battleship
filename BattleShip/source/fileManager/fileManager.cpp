#include "fileManager.h"

#include "gameState.h"

#include <fstream>
#include <string>

FileManager::FileManager(std::string file, bool write_mode)
{
    if (write_mode) {
		out.open(file);
		if (!(out.is_open())) {
            throw std::runtime_error("Error in opening Output stream");
        }

	} else {
		in.open(file);
		if (!(in.is_open())) {
            throw std::runtime_error("Error in opening Input stream");
        }
	}
}

FileManager::~FileManager()
{
    if (in.is_open()) {
        in.close(); 
    }
	
	if (out.is_open()) {
        out.close();
    }
}

void FileManager::write(GameState& state)
{
    if (!(out.is_open())) {
        throw std::runtime_error("Error: Output stream isn't open");
    }

    out << state;
}

void FileManager::read(GameState& state)
{
    if (!(in.is_open())) {
        throw std::runtime_error("Error: Input stream isn't open");
    }

    in >> state;
}