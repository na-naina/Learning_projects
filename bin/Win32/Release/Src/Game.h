#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "NxN.h"
#include "GraphMatrix.h"
#include <stack>
#include "State.h"

class Game
{
private:
	//variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::VideoMode* windowSize;
	float W, H;


	TitleScreen* mainMenu;
	GameSession* gamesession;

	int State = 0;
	

	sf::Clock dtClock;
	float dt;

	//initialization
	void initWindow();
	void initGamegrid();
	
	

public:
	


	Game();
	Game(float Width, float Height);

	virtual ~Game();

	//functions
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();




};

