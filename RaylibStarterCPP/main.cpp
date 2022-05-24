#include "Menu.h"
#include "Game.h"

int main(int argc, char* argv[])
{
    InitWindow(800, 600, "PING PONG");
    SetTargetFPS(60);

    Menu menu = Menu();
    Game game = Game();

    menu.Initial();
    game.Initial();
    menu.MenuLoop();
    CloseWindow();
    return 0;
}