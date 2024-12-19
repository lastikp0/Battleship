#ifndef GAME
#define GAME

#include "gameState.h"
#include "fileManager.h"

#include <vector>
#include <stdexcept>

class Game
{
public:
    Game();
    ~Game();

    void setParticipantsCount(int player_count, int bot_count);
    void createParticipants();
    
    void initBot(Participant* participant, Coords field_size, std::vector<int> ship_sizes);
    void initPlayer(Participant* participant, Coords field_size, std::vector<int> ship_sizes);

    void placeShip(Participant* participant, int index, Coords coords, ShipOrientation orientation);

    void start();
    void restart();

    void attack(Coords coords);
    void ability(IAbilitySettings* settings);

    void setTarget(int index);

    void save(std::string& file);
    bool isSaved();
    bool load(std::string& file);

    GameStatus getGameStatus() const noexcept;
    Coords getRoundMove() const noexcept;

    int getParticipantCount() const noexcept;

    int getCurrentIndex() noexcept;
    int getTargetIndex() noexcept;
    Participant* getParticipant(int index) const;

    bool isPlayerWinner() const noexcept;

private:
    int getAliveParticipantCount() const noexcept;

    GameState game_state_;
    FileManager* file_manager;

    int target_index_;
};

#endif