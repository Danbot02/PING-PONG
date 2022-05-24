#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "math.h"
#include "raylib.h"
#include "raygui.h"

class Menu
{
public:
	Menu();
	~Menu();

	void Initial();
	void MenuLoop();

	Color colour(int col);

	int screenWidth;
	int screenHeight;

	int mouseXPos;
	int mouseYPos;

	int button1Col;
	int button2Col;
};