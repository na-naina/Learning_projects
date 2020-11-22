#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "NxN.h"

class GraphMatrix
{
private:
	float Scale;
	NxN* Grid;
	float tileSize;
	std::vector<sf::RectangleShape> TileSprites;
	int CurrentTileX, CurrentTileY;
	sf::Music tileoverhover;

public:
	GraphMatrix();

	GraphMatrix(int Size, float Scale);

	GraphMatrix(int Size, float Scale, int WinCondition, int PlayerNumber);

	~GraphMatrix();

	void DrawMatrix(sf::RenderWindow* window);

	void UpdateHoverOverTile(sf::Event sfevent);

	void ClickOnTile();

	void UpdateMatrix();

	void UpdateCurrentTile(int x, int y);

	NxN* GetGrid() {
		return Grid;
	}

};

