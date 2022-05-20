#include "game.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "math.h"
#include "raylib.h"
#include "raygui.h"

Game::Game() {}

Game::~Game() {}

void Game::Initial()
{
    //Initialization of game window
    screenWidth = 800;
    screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "PING PONG");
    SetTargetFPS(60);

    playing = false;

    playerSpeed = 4;
    enemySpeed = 4;
    DifficultySpeed = 4;
    ballSpeed = 4;

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
}

void Game::GameLoop()
{
    //Main game loop
    while (!IsKeyPressed(KEY_ESCAPE))
    {
        if (playing == false && IsKeyDown(KEY_SPACE))
        {
            ballXPos = PP1.x + 5;
            ballYPos = PP1.y + 50;
            ballSpeed = 4;

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

            if (ballYPos < EP1.y + 50)
            {
                if (ballYDir > 0)
                {
                    EP1.y -= ballYDir * DifficultySpeed;
                    EP2.y -= ballYDir * DifficultySpeed;
                }
                else
                    if (ballYDir < 0)
                    {
                        EP1.y += ballYDir * DifficultySpeed;
                        EP2.y += ballYDir * DifficultySpeed;
                    }
            }

            if (ballYPos > EP2.y - 50)
            {
                if (ballYDir > 0)
                {
                    EP1.y += ballYDir * DifficultySpeed;
                    EP2.y += ballYDir * DifficultySpeed;
                }
                else
                    if (ballYDir < 0)
                    {
                        EP1.y -= ballYDir * DifficultySpeed;
                        EP2.y -= ballYDir * DifficultySpeed;
                    }
            }

            if (ballXPos <= PP1.x + 5 && ballYPos > PP1.y - 2 && ballYPos < PP2.y + 2)
            {
                ballXDir = ballXDir * (-1);
                ballSpeed += 0.1;
            }

            if (ballXPos >= EP1.x - 5 && ballYPos > EP1.y - 2 && ballYPos < EP2.y + 2)
            {
                ballXDir = ballXDir * (-1);
                ballSpeed += 0.1;
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
                PP1.y = 300 - 50;
                PP2.y = 300 + 50;
                EP1.y = 300 - 50;
                EP2.y = 300 + 50;
                playing = false;
            }
            else
                if (ballXPos >= screenWidth - 25)
                {
                    playerScore += 1;
                    PP1.y = 300 - 50;
                    PP2.y = 300 + 50;
                    EP1.y = 300 - 50;
                    EP2.y = 300 + 50;
                    playing = false;
                }
        }

        std::string s1 = std::to_string(playerScore);
        s1.append(" || ");
        s1.append(std::to_string(enemyScore));
        scoreBT = s1.c_str();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(scoreBT, screenWidth / 2 - sizeof(scoreBT) - 20, 20, 20, BLACK);

        DrawLineEx(TLC, TRC, 10, BLACK);
        DrawLineEx(TRC, BRC, 10, BLACK);
        DrawLineEx(BRC, BLC, 10, BLACK);
        DrawLineEx(BLC, TLC, 10, BLACK);

        DrawLineEx(PP1, PP2, 10, BLACK);
        DrawLineEx(EP1, EP2, 10, BLACK);
        DrawCircle(ballXPos, ballYPos, 5, BLACK);

        EndDrawing();
    }
}