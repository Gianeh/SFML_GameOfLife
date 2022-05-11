#include "GameOfLife.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

GameOfLife::GameOfLife()
{
	start = false;
	// loads config file
	loadConfig();
	// After configuration sets the parameters
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(-0.5);
	shape.setSize(sf::Vector2f(res, res));
	screen = new sf::RenderWindow(sf::VideoMode(Front.row() * res, Front.col() * res),
								  "GAME OF LIFE", sf::Style::Close | sf::Style::Titlebar);
	screen->setFramerateLimit(fps);

	// set the random seed
	srand(time(0));

	// First Init to dead screen
	for (i = 0; i < Front.row(); i++)
	{
		for (j = 0; j < Front.col(); j++)
		{
			Front(i, j) = false; // sets the rectangles state to dead (false);

			Front(i, j) ? shape.setFillColor(sf::Color::Black) : shape.setFillColor(sf::Color::White); // assign color based on cell state //OBV here it becomes white due to the state init above

			relativePosition = sf::Vector2f(j * res, i * res); // Size is a constant (resolution), position is calculated here  //j represents the columns so it changes the X and vice versa
			shape.setPosition(relativePosition);

			screen->draw(shape);
		}
	}
	// sample setup to check mistakes
	/*
	Front(10,5) = true;
	shape.setPosition(sf::Vector2f(5 * res, 10 * res));
	shape.setFillColor(sf::Color::Black);
	screen->draw(shape);
	Rear = Front; //IF WORKS, COPY THE FRONT MATRIX OVER THE NEXT GEN (REAR)
	*/
	screen->display(); // Swaps the buffers the first time to show initialization of cells (by default all dead)
}
GameOfLife::~GameOfLife()
{
	std::cout << "THANKS FOR 'PLAYING' MY VERSION OF THIS BEAUTIFUL GAME" << std::endl;
	std::cout << "FOR ANY ADVICE OR COLABORATION CONTACT ME DIRECTLY AT: pietropianigiani2@gmail.com" << std::endl;
	if (screen != nullptr)
		delete screen;
}
void GameOfLife::randomInit()
{
	for (i = 0; i < Front.row(); i++)
	{
		for (j = 0; j < Front.col(); j++)
		{
			int(rand()) % 2 ? Front(i, j) = false : Front(i, j) = true;								   // if random integer is even -> cell is dead, if odd -> is alive
			Front(i, j) ? shape.setFillColor(sf::Color::Black) : shape.setFillColor(sf::Color::White); // assign color based on cell state
			relativePosition = sf::Vector2f(j * res, i * res);										   // Size is a constant (resolution), position is calculated here
			shape.setPosition(relativePosition);
			screen->draw(shape);
		}
	}
	screen->display(); // Swaps the buffers the second time (after class Constructor) to show random first gen
}

void GameOfLife::play()
{
	// Actual rules of game starts if play button is pressed (has to be declared in main and passed to GameOfLife object)
	if (start)
	{
		int neigs;
		for (i = 0; i < Front.row(); i++)
		{
			for (j = 0; j < Front.col(); j++)
			{
				neigs = 0;

				//RULES TO UPDATE NEIGHBOURS COUNT
					if (i == 0){
						if (j == 0) {
							//top left corner
							if (Front(i    ,j + 1)) neigs++;
							if (Front(i + 1,j    )) neigs++;
							if (Front(i + 1,j + 1)) neigs++;
						}
						else if (j == Front.col()-1) {
							//top right corner
							if (Front(i    ,j - 1)) neigs++;
							if (Front(i + 1,j - 1)) neigs++;
							if (Front(i + 1,j    )) neigs++;
						}
						else {
							//mid top row
							if (Front(i    ,j - 1)) neigs++;
							if (Front(i    ,j + 1)) neigs++;
							if (Front(i + 1,j - 1)) neigs++;
							if (Front(i + 1,j    )) neigs++;
							if (Front(i + 1,j + 1)) neigs++;
						}
				}else if(i == Front.row()-1){
						if (j == 0) {
							//bottom left corner
							if (Front(i - 1,j    )) neigs++;
							if (Front(i - 1,j + 1)) neigs++;
							if (Front(i    ,j + 1)) neigs++;
						}
						else if (j == Front.col()-1) {
							//bottom right corner
							if (Front(i - 1,j    )) neigs++;
							if (Front(i - 1,j - 1)) neigs++;
							if (Front(i    ,j - 1)) neigs++;
						}
						else {
							//mid bottom row
							if (Front(i - 1,j - 1)) neigs++;
							if (Front(i - 1,j    )) neigs++;
							if (Front(i - 1,j + 1)) neigs++;
							if (Front(i    ,j - 1)) neigs++;
							if (Front(i    ,j + 1)) neigs++;
						}
				}else{ //i != 0 or R-1
						if (j == 0) {
							//mid left col
							if (Front(i - 1,j    )) neigs++;
							if (Front(i - 1,j + 1)) neigs++;
							if (Front(i    ,j + 1)) neigs++;
							if (Front(i + 1,j + 1)) neigs++;
							if (Front(i + 1,j    )) neigs++;
						}
						else if (j == Front.col()-1) {
							//mid right col
							if (Front(i - 1,j    )) neigs++;
							if (Front(i - 1,j - 1)) neigs++;
							if (Front(i    ,j - 1)) neigs++;
							if (Front(i + 1,j - 1)) neigs++;
							if (Front(i + 1,j    )) neigs++;
						}
						else {
							//default case
							if (Front(i - 1,j - 1)) neigs++;
							if (Front(i - 1,j    )) neigs++;
							if (Front(i - 1,j + 1)) neigs++;
							if (Front(i    ,j - 1)) neigs++;
							if (Front(i    ,j + 1)) neigs++;
							if (Front(i + 1,j - 1)) neigs++;
							if (Front(i + 1,j    )) neigs++;
							if (Front(i + 1,j + 1)) neigs++;

						}
							
				}
				updateNext(neigs);
				drawNext();
			}
		}
		screen->display();
		Front = Rear;
	}
}

void GameOfLife::updateNext(int neigs)
{
	if (neigs < 2)
	{
		Rear(i, j) = false; // die by underpopulation (or stay dead if dead)
	}
	else if ((neigs == 2 || neigs == 3) && Front(i, j))
	{
		Rear(i, j) = true; // stay alive
	}
	else if (neigs == 3 && !Front(i, j))
	{
		Rear(i, j) = true; // Spawn
	}
	else if (neigs > 3)
	{
		Rear(i, j) = false; // die by overpopulation (or stay dead)
	}
}

void GameOfLife::drawNext()
{
	Rear(i, j) ? shape.setFillColor(sf::Color::Black) : shape.setFillColor(sf::Color::White); // update the color baseed on state of cell
	// CELL POSITION IS CALCULATED EVERY FRAME FOR EVERY SINGLE CELL (using a single sf::RectangleShape object)
	relativePosition = sf::Vector2f(j * res, i * res);
	shape.setPosition(relativePosition);
	screen->draw(shape);
}

// With this configuration setting.txt must be written in the same exact way as the original
// informations are retrieved line by line and a single line shift would break the loop
// for any problem use the default or call "manual" to use manual settings
void GameOfLife::loadConfig()
{
	// DEFAULT
	int R, C, Res;
	R = 125, C = 125, Res = 5;
	fps = 5;

	std::string input;
	std::cout << std::endl;
	std::cout << "Hello dear User," << std::endl
			  << "to play my humble version of 'Game of Life'" << std::endl
			  << "enter here the path to your 'config.txt' file or write 'manual' to manually insert size: ";
	std::cin >> input;

	if (input == "manual" || input == "Manual")
	{
		std::cout << std::endl
				  << "Insert number of Rows: ";
		std::cin >> R;
		std::cout << std::endl
				  << "Insert number of Columns: ";
		std::cin >> C;
		std::cout << std::endl
				  << "Insert size of Squares: ";
		std::cin >> Res;
		std::cout << std::endl
				  << "Insert Frame rate limit: ";
		std::cin >> fps;
	}
	else
	{
		// search for config.txt files
		std::ifstream config(input);
		if (!config)
		{
			std::cout << "Config File not found! Default settings configuration" << std::endl;
			std::cout << "Press Enter to start" << std::endl;
		}
		else
		{
			std::string skip;
			std::string get;
			getline(config, skip);
			std::cout << skip << std::endl;
			getline(config, skip);
			std::cout << skip << std::endl;

			// GET RESOLUTION
			getline(config, get);
			Res = stoi(get);
			std::cout << Res << std::endl;

			getline(config, skip);
			std::cout << skip << std::endl;

			// GET ROWS
			getline(config, get);
			R = stoi(get);
			std::cout << R << std::endl;

			getline(config, skip);
			std::cout << skip << std::endl;

			// GET COLUMNS
			getline(config, get);
			C = stoi(get);
			std::cout << C << std::endl;

			getline(config, skip);
			std::cout << skip << std::endl;

			// GET FRAMERATE
			getline(config, get);
			fps = stoi(get);
			std::cout << get << std::endl;

			config.close();

			std::cout << std::endl
					  << "Config File Read Succesfully" << std::endl;
			std::cout << "Press Enter to start" << std::endl;
		}
	}
	Front.reAllocate(R, C);
	Rear.reAllocate(R, C);
	res = Res;
}

void GameOfLife::loop()
{
	while (screen->isOpen())
	{
		while (screen->pollEvent(e))
		{
			if (e.type == e.Closed)
				screen->close();
		}
		if (key.isKeyPressed(sf::Keyboard::Enter))
			start = !start;
		play();
	}
}