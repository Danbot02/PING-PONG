#include "Menu.h"
#include "Game.h"
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
    screenWidth = GetScreenWidth(); //Gets the current Screen Width for later use
    screenHeight = GetScreenHeight(); //Gets the current Screen Height for later use

    playing = false;

    //Setting the speed and difficulty of the player, enemy and the ball
    playerSpeed = 4;
    difficultySpeed = 4;
    ballSpeed = 4;

    //Setting the points for the game border
    TLC.x = 0;
    TLC.y = 60;
    TRC.x = screenWidth;
    TRC.y = 60;
    BLC.x = 0;
    BLC.y = screenHeight;
    BRC.x = screenWidth;
    BRC.y = screenHeight;

    //Setting the starting position for the player
    PP1.x = 50;
    PP1.y = 300 - 50;
    PP2.x = 50;
    PP2.y = 300 + 50;

    //Setting the starting position for the enemy
    EP1.x = screenWidth - 50;
    EP1.y = 300 - 50;
    EP2.x = screenWidth - 50;
    EP2.y = 300 + 50;

    //Setting the starting position for the ball
    ballXPos = PP1.x + 5;
    ballYPos = PP1.y + 50;

    std::cout << "Game Initialized" << std::endl;
}

void Game::GameLoop1()
{
    //Main game loop
    while (!IsKeyPressed(KEY_ESCAPE))
    {
        if (playing == false && IsKeyDown(KEY_SPACE)) //Checks if playing is false and if the space bar key is pressed down
        {
            PP1.y = 300 - 50;
            PP2.y = 300 + 50;
            EP1.y = 300 - 50;
            EP2.y = 300 + 50;
            ballXPos = PP1.x + 5;
            ballYPos = PP1.y + 50;
            ballSpeed = 4;
            
            srand(static_cast <unsigned> (time(0)));//Reseeds the rand function with time
            ballAngle = static_cast <float> (rand() % 50); //Generates a rand num between 0-50 used for starting angle
            int PN = rand() % 2; //Generates a rand num between 0-1 used for determining starting direction of the ball
            ballAngle = ballAngle * (PI / 180); //Converts degrees to radians

            if (PN == 1) //If the rand num PN is 1 then invert the rand num for angle to a negitive
            {
                ballAngle = ballAngle * (-1);
            }

            ballXDir = cos(ballAngle); //Takes the balls angle and turns it into horizontal movement % using cos
            ballYDir = sin(ballAngle); //Takes the balls angle and turns it into vertical movement % using sin
            playing = true;
        }

        if (playing) //Playing game loop
        {
            ballXPos += ballXDir * ballSpeed; //Changes the balls X position by adding its self to the horizontal movement % multiplied by the overall ball speed
            ballYPos += ballYDir * ballSpeed; //Changes the balls Y position by adding its self to the vertical movement % multiplied by the overall ball speed

            if (IsKeyDown(KEY_UP) == true && PP1.y > 60) //If the up arrow is pressed and the stick is within height limit then move the player upwards by the defined speed
            {
                PP1.y -= playerSpeed;
                PP2.y -= playerSpeed;
            }

            if (IsKeyDown(KEY_DOWN) == true && PP2.y < screenHeight) //If the down arrow is pressed and the stick is within height limit then move player downwards by the defined speed
            {
                PP1.y += playerSpeed;
                PP2.y += playerSpeed;
            }

            //If the ball Y pos is less than the center point of enemy stick the edge of stick is not at border limit, move enemy stick up
            //The movement of the ball is either negitive or positive and thus the movement of the stick is the reverse of that
            if (ballYPos < EP1.y + 50 && EP1.y > 60) 
            {
                if (ballYDir > 0)
                {
                    EP1.y -= ballYDir * difficultySpeed;
                    EP2.y -= ballYDir * difficultySpeed;
                }
                else
                if (ballYDir < 0)
                {
                    EP1.y += ballYDir * difficultySpeed;
                    EP2.y += ballYDir * difficultySpeed;
                }
            }

            //If the ball Y pos is greater than the center point of enemy stick the edge of stick is not at border limit, move enemy stick down
            //The movement of the ball is either negitive or positive and thus the movement of the stick is the reverse of that
            if (ballYPos > EP2.y - 50 && EP2.y < screenHeight)
            {
                if (ballYDir > 0)
                {
                    EP1.y += ballYDir * difficultySpeed;
                    EP2.y += ballYDir * difficultySpeed;
                }
                else
                if (ballYDir < 0)
                {
                    EP1.y -= ballYDir * difficultySpeed;
                    EP2.y -= ballYDir * difficultySpeed;
                }
            }

            if (ballXPos <= PP1.x + 5 && ballYPos > PP1.y - 2 && ballYPos < PP2.y + 2) //If the ball hits the right-side of the player then reverse the ball X directional % and increase overal ball speed
            {
                ballXDir = ballXDir * (-1);
                ballSpeed += 0.1;
            }

            if (ballXPos >= EP1.x - 5 && ballYPos > EP1.y - 2 && ballYPos < EP2.y + 2) //If the ball hits the left-side of the enemy then reverse the ball X directional % and increase overal ball speed
            {
                ballXDir = ballXDir * (-1);
                ballSpeed += 0.1;
            }

            if (ballYPos <= 70 || ballYPos >= screenHeight - 10) //If the ball Y position is > = < the game border upper/lower limit then invert the vertical directional %
            {
                ballYDir = ballYDir * (-1);
            }

            if (ballXPos <= 25) //If the ball X position is less than 25 then add 1 point to the enemy and stop play
            {
                enemyScore += 1;
                playing = false;
            }
            else
            if (ballXPos >= screenWidth - 25) //If the ball X position is greater than the screen width -25 then add 1 point to the player and stop play
            {
                playerScore += 1;
                playing = false;
            }
        }

        std::string s1 = std::to_string(playerScore); //Creates a string named s1 and writes the playerScore int to it
        s1.append(" || "); //Appends " || " to the end of s1
        s1.append(std::to_string(enemyScore)); //Appends the enemyScore int to the end of s1
        scoreBT = s1.c_str(); //Converts s1 string to a const char array

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

void Game::GameLoop2()
{
    //Main game loop
    while (!IsKeyPressed(KEY_ESCAPE))
    {
        if (playing == false && IsKeyDown(KEY_SPACE)) //Checks if playing is false and if the space bar key is pressed down
        {
            PP1.y = 300 - 50;
            PP2.y = 300 + 50;
            EP1.y = 300 - 50;
            EP2.y = 300 + 50;
            ballXPos = PP1.x + 5;
            ballYPos = PP1.y + 50;
            ballSpeed = 4;

            srand(static_cast <unsigned> (time(0)));//Reseeds the rand function with time
            ballAngle = static_cast <float> (rand() % 50); //Generates a rand num between 0-50 used for starting angle
            int PN = rand() % 2; //Generates a rand num between 0-1 used for determining starting direction of the ball
            ballAngle = ballAngle * (PI / 180); //Converts degrees to radians

            ballAngle = 0;

            if (PN == 1) //If the rand num PN is 1 then invert the rand num for angle to a negitive
            {
                ballAngle = ballAngle * (-1);
            }

            ballXDir = cos(ballAngle); //Takes the balls angle and turns it into horizontal movement % using cos
            ballYDir = sin(ballAngle); //Takes the balls angle and turns it into vertical movement % using sin
            playing = true;
        }

        if (playing)
        {
            ballXPos += ballXDir * ballSpeed; //Changes the balls X position by adding its self to the horizontal movement % multiplied by the overall ball speed
            ballYPos += ballYDir * ballSpeed; //Changes the balls Y position by adding its self to the vertical movement % multiplied by the overall ball speed

            if (IsKeyDown(KEY_W) == true && PP1.y > 60) //If the W key is pressed and the stick is within height limit then move the player1 upwards by the defined speed
            {
                PP1.y -= playerSpeed;
                PP2.y -= playerSpeed;
            }

            if (IsKeyDown(KEY_S) == true && PP2.y < screenHeight) //If the S key is pressed and the stick is within height limit then move player1 downwards by the defined speed
            {
                PP1.y += playerSpeed;
                PP2.y += playerSpeed;
            }

            if (IsKeyDown(KEY_UP) == true && EP1.y > 60) //If the up arrow is pressed and the stick is within height limit then move the player2 upwards by the defined speed
            {
                EP1.y -= playerSpeed;
                EP2.y -= playerSpeed;
            }

            if (IsKeyDown(KEY_DOWN) == true && EP2.y < screenHeight) //If the down arrow key is pressed and the stick is within height limit then move player2 downwards by the defined speed
            {
                EP1.y += playerSpeed;
                EP2.y += playerSpeed;
            }

            if (ballXPos <= PP1.x + 5 && ballYPos > PP1.y - 2 && ballYPos < PP2.y + 2) //If the ball hits the right-side of the player then reverse the ball X directional speed and increase overal ball speed
            {
                ballXDir = ballXDir * (-1);
                ballSpeed += 0.1;
            }

            if (ballXPos >= EP1.x - 5 && ballYPos > EP1.y - 2 && ballYPos < EP2.y + 2) //If the ball hits the left-side of the enemy then reverse the ball X directional speed and increase overal ball speed
            {
                ballXDir = ballXDir * (-1);
                ballSpeed += 0.1;
            }

            if (ballYPos >= screenHeight - 10) //If the ball Y position is > or = the screen height - 10 (The game border lower limit) then invert the vertical directional speed
            {
                ballYDir = ballYDir * (-1);
            }

            if (ballYPos <= 70) //If the ball Y position is < or = 70 (The game border upper limit) then invert the vertical directional speed
            {
                ballYDir = ballYDir * (-1);
            }

            if (ballXPos <= 25) //If the ball X position is less than 25 then add 1 point to the enemy and stop play
            {
                enemyScore += 1;
                playing = false;
            }
            else
                if (ballXPos >= screenWidth - 25) //If the ball X position is greater than the screen width -25 then add 1 point to the player and stop play
                {
                    playerScore += 1;
                    playing = false;
                }
        }

        std::string s1 = std::to_string(playerScore); //Creates a string named s1 and writes the playerScore int to it
        s1.append(" || "); //Appends " || " to the end of s1
        s1.append(std::to_string(enemyScore)); //Appends the enemyScore int to the end of s1
        scoreBT = s1.c_str(); //Converts s1 string to a const char array

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