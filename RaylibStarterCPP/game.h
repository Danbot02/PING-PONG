/*
* Game Class Summary
* The Game Class is used for running the actualy intended game and keeping all
* of its values aside so other functions can not mess with them. Both single player
* and multi player are put into the same class as they both use the exact same values
* how ever each function has a slight difference that being that the multiplayer replaces
* the AI control portion with a Human control protion allowing each stick to be
* player controlled.
*/

#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "math.h"
#include "raylib.h"
#include "raygui.h"

class Game
{
public:
	Game(); //Game constructor
	~Game(); //Game deconstructor

	void Initial(); //Initialization function for setting all the values
	void GameLoop1(); //Main loop function for single player that will indefinatly run until either the program is closed or the escape button is held down
	void GameLoop2(); //Main loop function for multi player that will indefinatly run until either the program is closed or the escape button is held down

private:
	int screenWidth;
	int screenHeight;

	Vector2 TLC; //X and Y position for the Top Left Corner of the game border
	Vector2 TRC; //X and Y position for the Top Right Corner of the game border
	Vector2 BLC; //X and Y position for the Bottom Left Corner of the game border
	Vector2 BRC; //X and Y position for the Bottom Right Corner of the game border

	Vector2 PP1; //X and Y position for the top point of the player stick
	Vector2 PP2; //X and Y position for the bottom point of the player stick

	Vector2 EP1; //X and Y position for the top point of the enemy stick
	Vector2 EP2; //X and Y position for the bottom point of the enemy stick

	const char* scoreBT; //Const Char* for use of displaying the scoreboard

	int playerSpeed; //The speed level which determins how fast the player stick can more used in both single and multi player
	int DifficultySpeed; //Difficulty speed level which determins how fast the enemy stick can more in single player

	int playerScore; //The score for the player
	int enemyScore; //The score for the enemy and second player

	bool playing; //Bool for determining if the game is in play or not
	float ballAngle; //The angle of trajectory of the ball
	float ballSpeed; //The overall speed of the ball
	float ballXDir; //The x directional % of the ball
	float ballYDir; //The y directional % of the ball
	float ballXPos; //The x position of the ball
	float ballYPos; //The y position of the ball
};