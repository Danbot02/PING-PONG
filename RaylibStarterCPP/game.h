#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "math.h"
#include "raylib.h"
#include "raygui.h"


#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

class Game
{
public:
	Game();
	~Game();

	void Initial();
	void GameLoop();

	int screenWidth;
	int screenHeight;

	Vector2 TLC;
	Vector2 TRC;
	Vector2 BLC;
	Vector2 BRC;

	Vector2 PP1;
	Vector2 PP2;

	Vector2 EP1;
	Vector2 EP2;

	const char* scoreBT;

	int DifficultySpeed;

	int playerSpeed;
	int playerScore;

	int enemySpeed;
	int enemyScore;

	bool playing;
	float ballAngle;
	float ballSpeed;
	float ballXDir;
	float ballYDir;
	float ballXPos;
	float ballYPos;
};