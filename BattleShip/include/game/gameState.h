#ifndef GAME_STATE
#define GAME_STATE

#include "shipManager.h"
#include "field.h"
#include "abilityManager.h"

#include "participant.h"
#include "bot.h"
#include "player.h"

#include "hasher.h"

#include <vector>
#include <fstream>
#include <sstream>

enum class GameStatus : int
{
    active,
    finished
};

struct ShipInfo
{
    int x, y;
    int orientation;
    int size;
    std::vector<int> segments_health;
};

struct GameState
{
    std::vector<Participant*> participants_;
    GameStatus status_;

    int current_participant_index_;
    bool ability_used_;
    int round_count_;
    int move_count_;

    int player_count_;
    int bot_count_;

    bool load_ = false;
    bool save_ = false;

    friend std::ifstream& operator>>(std::ifstream& in, GameState& state);
    friend std::ofstream& operator<<(std::ofstream& out, GameState& state);
};

#endif