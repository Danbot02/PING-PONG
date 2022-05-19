#include "menu.h"
#include "game.h"
#include "raylib.h"
#include "raygui.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

int menuloop(int argc, char* argv[])
{
    //Initialization of Menu window
    int screenWidth = 600;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "PING PONG");
    SetTargetFPS(60);

    //Main menu loop
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_ENTER))
        {
            game(gameloop());
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("PING  PONG", 300 - 5, 300, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}