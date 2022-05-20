#include "game.h"

int main(int argc, char* argv[])
{
    Game game = Game();
    game.Initial();
    game.GameLoop();
    CloseWindow();
    return 0;
}