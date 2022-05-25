#include "Menu.h"
#include "Game.h"

Menu::Menu() {}
Menu::~Menu() {}

void Menu::Initial()
{
    mouseXPos = 0;
    mouseYPos = 0;

    std::cout << "Menu Initialized" << std::endl;
}

void Menu::MenuLoop()
{
    while (!IsKeyPressed(KEY_ESCAPE))
    {
        mouseXPos = GetMouseX(); //Gets the current mouse X position
        mouseYPos = GetMouseY(); //Get the current mouse Y position

        //If the X and Y position of the mouse are within a set range then change the colour of the box it is inside
        //If mouse button 0 is pressed, change the colour again
        //When the mouse button is released create a new instance of the Game class, run the Initial function then run the GameLoop for 1 player
        if (mouseXPos > 270 && mouseXPos < 380 && mouseYPos > 335 && mouseYPos < 385)
        {
            button1Col = 1;
            if (IsMouseButtonDown(0))
            {
                button1Col = 2;
            }
            else
            if (IsMouseButtonReleased(0))
            {
                Game game = Game();
                game.Initial();
                game.GameLoop1();
            }
        }
        else //if the mouse X and Y position are out of the defined bounds then set the box to its original colour
        {
            button1Col = 0;
        }


        //If the X and Y position of the mouse are within a set range then change the colour of the box it is inside
        //If mouse button 0 is pressed, change the colour again
        //When the mouse button is released create a new instance of the Game class, run the Initial function then run the GameLoop for 2 player
        if (mouseXPos > 440 && mouseXPos < 550 && mouseYPos > 335 && mouseYPos < 385)
        {
            button2Col = 1;
            if (IsMouseButtonDown(0))
            {
                button2Col = 2;
            }
            else
            if (IsMouseButtonReleased(0))
            {
                Game game = Game();
                game.Initial();
                game.GameLoop2();
            }
        }
        else //if the mouse X and Y position are out of the defined bounds then set the box to its original colour
        {
            button2Col = 0;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("PING PONG", 270, 265, 50, BLACK); //Writes "PING PONG" at the center of the screen in black
        DrawRectangle(270, 335, 110, 50, colour(button1Col)); //Draws a rectangle with the defined colour
        DrawRectangle(440, 335, 110, 50, colour(button2Col)); //Draws a rectangle with the defined colour
        DrawText("1-Player", 285, 350, 20, WHITE); //Writes "1-Player" in the middle of the first box in white
        DrawText("2-Player", 453, 350, 20, WHITE); //Writes "2-Player" in the middle of the second box in white

        EndDrawing();
    }
}

Color Menu::colour(int col) //A function that takes an int and returns a color based on the number given
{
    switch (col)
    {
    case (0):
        return BLACK;

    case (1):
        return GRAY;

    case (2):
        return LIGHTGRAY;

    case (3):
        return WHITE;

    default:
        break;
    }
}