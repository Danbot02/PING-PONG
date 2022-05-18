#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "math.h"
#include "raylib.h"
#include "raygui.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define MAX_DIGI 2

Vector2 TLC;
Vector2 TRC;
Vector2 BLC;
Vector2 BRC;

Vector2 PP1;
Vector2 PP2;

Vector2 EP1;
Vector2 EP2;

int playerSpeed = 2;
int playerScore = 0;
const char *playerScoreT;

int enemySpeed = 2;
int enemyScore = 0;
const char *enemyScoreT;

bool playing = false;
float ballAngle;
int ballSpeed = 2;
float ballXDir = 0;
float ballYDir = 0;
float ballXPos = 0;
float ballYPos = 0;

int main(int argc, char* argv[])
{
    //Initialization
    int screenWidth = 800;
    int screenHeight = 600;

    TLC.x = 0;
    TLC.y = 60;
    TRC.x = screenWidth;
    TRC.y = 60;
    BLC.x = 0;
    BLC.y = screenHeight;
    BRC.x = screenWidth;
    BRC.y = screenHeight;

    PP1.x = 50;
    PP1.y = 300 - 50;
    PP2.x = 50;
    PP2.y = 300 + 50;

    EP1.x = screenWidth - 50;
    EP1.y = 300 - 50;
    EP2.x = screenWidth - 50;
    EP2.y = 300 + 50;

    ballXPos = PP1.x + 5;
    ballYPos = PP1.y + 50;

    InitWindow(screenWidth, screenHeight, "PING PONG");

    SetTargetFPS(60);

    //Main game loop
    while (!WindowShouldClose())
    {
        if (playing == false && IsKeyDown(KEY_SPACE))
        {
            srand(static_cast <unsigned> (time(0)));
            ballAngle = static_cast <float> (rand() % 50);
            int PN = rand() % 2;
            ballAngle = ballAngle * (PI / 180);

            std::cout << PN << std::endl;

            if (1 == 1)
            {
                ballAngle = ballAngle * (-1);
            }

            std::cout << ballAngle << std::endl;
            ballXDir = cos(ballAngle);
            ballYDir = sin(ballAngle);
            playing = true;
        }

        if (playing)
        {
            ballXPos += ballXDir * ballSpeed;
            ballYPos += ballYDir * ballSpeed;
        }

        if (IsKeyDown(KEY_UP) == true)
        {
            PP1.y -= playerSpeed;
            PP2.y -= playerSpeed;
        }

        if (IsKeyDown(KEY_DOWN) == true)
        {
            PP1.y += playerSpeed;
            PP2.y += playerSpeed;
        }

        if (ballYPos <= 600 - 10)
        {
            ballYDir = ballYDir * (-1);
        }

        if (ballYPos >= 70)
        {
            ballYDir = ballYDir * (-1);
        }

        if (ballXPos <= 25)
        {
            enemyScore += 1;
            ballXPos = PP1.x + 5;
            ballYPos = PP1.y + 50;
            playing = false;
        }
        else
        if (ballXPos >= screenWidth - 25)
        {
            playerScore += 1;
            ballXPos = PP1.x + 5;
            ballYPos = PP1.y + 50;
            playing = false;
        }

        std::string s1 = std::to_string(playerScore);
        playerScoreT = s1.c_str();

        std::string s2 = std::to_string(enemyScore);
        enemyScoreT = s2.c_str();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(playerScoreT, screenWidth / 2 - sizeof(playerScoreT) - 20, 20, 20, BLACK);
        DrawText("||", screenWidth / 2, 20, 20, BLACK);
        DrawText(enemyScoreT, screenWidth / 2 + sizeof(enemyScoreT) + 15, 20, 20, BLACK);

        DrawLineEx(TLC, TRC, 10, BLACK);
        DrawLineEx(TRC, BRC, 10, BLACK);
        DrawLineEx(BRC, BLC, 10, BLACK);
        DrawLineEx(BLC, TLC, 10, BLACK);

        DrawLineEx(PP1, PP2, 10, BLACK);
        DrawLineEx(EP1, EP2, 10, BLACK);
        DrawCircle(ballXPos, ballYPos, 5, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}