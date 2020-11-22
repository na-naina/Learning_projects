#pragma once
#include "GraphMatrix.h"

class GameSession 
{
private:

	GraphMatrix* GameGrid;
	sf::Text WinnerText;
	sf::Sound WinEffect;
	sf::Font font;
	sf::RectangleShape EndScrBackground;
	sf::Music GameEnded;
	float width, height;


public:

	bool isEnded;

	GameSession(float Width, float Height);

	GameSession(float Width, float Height, int Size, int WinCondition, int PlayerNumber);

	~GameSession();

	void render(sf::RenderWindow* window);

	void update();

	void drawEndScreen(sf::RenderWindow* window);

	void updateSFEvents(sf::Event sfEvent);

};






class TitleScreen
{
private:
	sf::Music BackgroundMusic;
	sf::Texture BackgroundImg;
	sf::Sprite BackgroundSprite;
	sf::Font font;
	sf::Text Title;
	sf::Text EnterValues;
	sf::Text Example;
	sf::Text Error;


	sf::RectangleShape InputField;
	sf::Text Input;

	std::string PlayerInput;

	

public:

	bool isEnded;

	TitleScreen(float Height, float Width);

	TitleScreen();

	void render(sf::RenderWindow* window);

	void update();

	void updateSFEvents(sf::Event sfEvent);

	std::string GetInput();

	bool InputIsValid(std::string InputString);

	int GetGridSize();
	int GetPlayerNumber();
	int GetWinCondition();

};
