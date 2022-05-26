#include "Menu.h"

int main(int argc, char* argv[])
{
    InitWindow(800, 600, "PING PONG"); //Create window of size 800 x 600 named PING PONG
    SetTargetFPS(60); //Set the target FPS to 60

    Menu menu = Menu(); //Create a new instance of Menu named menu

    menu.Initial(); //Run the Initial function of the Menu class
    menu.MenuLoop(); //Run the MenuLoop function of the Menu class
    CloseWindow(); //Closes the window
    return 0;
}