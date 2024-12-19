#include <iostream>
#include <ctime>

#include "game.h"
#include "gameController.h"

#include "terminalInput.h"
#include "terminalOutput.h"

int main()
{
    srand(time(0));

    Game game;

    GameController<TerminalInput, TerminalOutput> controller(game);
    controller.start();

    return 0;
}