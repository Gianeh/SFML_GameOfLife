#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <random>
#include <string.h>

#include "Matrix.h"


class GameOfLife {
	private:
		//Single reusable square object
		sf::RectangleShape shape;
		//Screen object
		sf::RenderWindow *screen;
		//Event handler
		sf::Event e;
		sf::Keyboard key;
		//Global index and cell resolution
		int i, j, res, fps;
		//This_gen Matrix and Next_gen Matrix
		Matrix Front;
		Matrix Rear;
		sf::Vector2f relativePosition;
		bool start;
		

	public:
        GameOfLife();
		~GameOfLife();
		void loadConfig();
        void randomInit();
        void play();
        void updateNext(int neigs);
		void drawNext();
		void loop();
};