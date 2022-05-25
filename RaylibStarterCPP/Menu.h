/*
* Menu Class Summary
* The Menu Class is for seperating the menu from the rest of the game meaning
* there is no need to load the entirety of the game from launch and instead
* means we can load only the portions we want based on what happens here
*/

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
	Menu(); //Menu constructor
	~Menu(); //Menu deconstructor

	void Initial(); //Initialization function for setting all the values
	void MenuLoop(); //Main loop function that will indefinatly run the menu until either the program is closed or another function is started

private:
	Color colour(int col); //Color set function that takes in a number and returns a designated color

	int mouseXPos; //X position for mouse
	int mouseYPos; //Y position for mouse

	int button1Col; //Button 1 Colour setting
	int button2Col; //Button 2 Colour setting
};