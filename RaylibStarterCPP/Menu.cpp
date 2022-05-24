#include "Menu.h"

Menu::Menu() {}
Menu::~Menu() {}

void Menu::Initial()
{
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    
    mouseXPos = 0;
    mouseYPos = 0;

    std::cout << "Menu Initialized" << std::endl;
}

void Menu::MenuLoop()
{
    while (!IsKeyPressed(KEY_ESCAPE))
    {
        mouseXPos = GetMouseX();
        mouseYPos = GetMouseY();

        if (mouseXPos > 270 && mouseXPos < 380 && mouseYPos > 335 && mouseYPos < 385)
        {
            button1Col = 1;
            if (IsMouseButtonDown(0))
            {
                button1Col = 2;
            }
        }
        else
        {
            button1Col = 0;
        }

        if (mouseXPos > 440 && mouseXPos < 550 && mouseYPos > 335 && mouseYPos < 385)
        {
            button2Col = 1;
            if (IsMouseButtonDown(0))
            {
                button2Col = 2;
            }
        }
        else
        {
            button2Col = 0;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("PING PONG", 270, 265, 50, BLACK);
        DrawRectangle(270, 335, 110, 50, colour(button1Col));
        DrawRectangle(440, 335, 110, 50, colour(button2Col));
        DrawText("1-Player", 285, 350, 20, WHITE);
        DrawText("2-Player", 453, 350, 20, WHITE);

        EndDrawing();
    }
}

Color Menu::colour(int col)
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