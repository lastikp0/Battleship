#ifndef GAME
#define GAME

#include "gameState.h"
#include "fileManager.h"

#include <vector>
#include <stdexcept>
#include <ctime>

class Game
{
public:
    Game();
    ~Game();

    void createParticipants(int player_count, int bot_count);

    void start(int player_count, int bot_count);
    void gameCycle();
    void restart();

    void runRound();
    void roundCycle();

    GameStatus getGameStatus() const noexcept;

    int getParticipantCount() const noexcept;
    int getAliveParticipantCount() const noexcept;

    bool isPlayerWinner() const noexcept;

private:
    Participant* createPlayer();
    Participant* createBot();

    GameState game_state_;
    FileManager* file_manager;
};

#endif