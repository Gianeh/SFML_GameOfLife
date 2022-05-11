#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameOfLife.h"

using namespace sf;



int main() {
	//Game object, contains two Matrix objects and parameters to run the rules for "GAME OF LIFE"
	GameOfLife Game;
	Game.randomInit();
	
	bool play = false;

	Game.loop();
	return 0;
}