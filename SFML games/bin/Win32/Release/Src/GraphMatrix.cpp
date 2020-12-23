#include "GraphMatrix.h"



GraphMatrix::GraphMatrix()
	:Scale(0), tileSize(0), CurrentTileX(-1), CurrentTileY(-1)
{
	Grid = new NxN();
	Grid->SetPlayerNumber(2);
}

GraphMatrix::GraphMatrix(int Size, float Scale, int WinCondition, int PlayerNumber)
	:Scale(Scale), CurrentTileX(-1), CurrentTileY(-1)
{

	tileoverhover.openFromFile("Src/resources/tileover.ogg");


	tileoverhover.setVolume(70);
	Grid = new NxN(Size, WinCondition);
	Grid->SetPlayerNumber(PlayerNumber);

	tileSize = (this->Scale / (float)this->Grid->GetSize());


	sf::RectangleShape T;
	T = sf::RectangleShape(sf::Vector2f(tileSize, tileSize));
	T.setOutlineThickness(-2.f);
	T.setOutlineColor(sf::Color(100, 100, 0));
	T.setFillColor(sf::Color(255, 255, 255));

	TileSprites.reserve(Size);

	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			TileSprites.push_back(T);


	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			TileSprites[i * Size + j].setPosition(tileSize * j, tileSize * i);
		}
	}

}

GraphMatrix::GraphMatrix(int Size, float Scale)
	:Scale(Scale), CurrentTileX(-1), CurrentTileY(-1)
{
	Grid = new NxN(Size, 3);
	Grid->SetPlayerNumber(2);

	tileSize = (this->Scale / (float)this->Grid->GetSize());


	sf::RectangleShape T;
	T = sf::RectangleShape(sf::Vector2f(tileSize, tileSize));
	T.setOutlineThickness(-2.f);
	T.setOutlineColor(sf::Color(100, 100, 0));
	T.setFillColor(sf::Color(255, 255, 255));

	TileSprites.reserve(Size);

	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			TileSprites.push_back(T);


	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			TileSprites[i * Size + j].setPosition(tileSize*j, tileSize * i);
		}
	}

}

GraphMatrix::~GraphMatrix()
{
	delete this->Grid;
}





void GraphMatrix::UpdateMatrix()
{
	int Size = this->Grid->GetSize();

	for(int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++) {
			if(Grid->GetField()[i*Size + j] == '_')
				TileSprites[i * Size + j].setFillColor(sf::Color(255, 255, 255));


			if (Grid->GetField()[i * Size + j] == 'a')
				TileSprites[i * Size + j].setFillColor(sf::Color(100, 0, 100));


			if (Grid->GetField()[i * Size + j] == 'a' + 1)
				TileSprites[i * Size + j].setFillColor(sf::Color(255, 0, 100));

			if (Grid->GetField()[i * Size + j] == 'a' + 2)
				TileSprites[i * Size + j].setFillColor(sf::Color(44, 88, 112));

			if (Grid->GetField()[i * Size + j] == 'a' + 3)
				TileSprites[i * Size + j].setFillColor(sf::Color(88, 88, 112));


			if (Grid->GetField()[i * Size + j] == 'a' + 4)
				TileSprites[i * Size + j].setFillColor(sf::Color(180, 180, 180));

			if (Grid->GetField()[i * Size + j] == 'a' + 5)
				TileSprites[i * Size + j].setFillColor(sf::Color(40, 180, 40));
		}


	if (CurrentTileY != -1)
	{
		sf::Color T = TileSprites[CurrentTileY * Size + CurrentTileX].getFillColor();
		T -= sf::Color(30, 30, 30, 0);
		TileSprites[CurrentTileY * Size + CurrentTileX].setFillColor(T);
	}

}



void GraphMatrix::DrawMatrix(sf::RenderWindow* window)
{
		
	int Size = this->Grid->GetSize();
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			window->draw(TileSprites[i * this->Grid->GetSize() + j]);
		}
	}

}




void GraphMatrix::UpdateHoverOverTile(sf::Event sfevent)
{
	if ((CurrentTileX != (int)trunc(sfevent.mouseMove.x/tileSize) || 
		(CurrentTileY != (int)trunc(sfevent.mouseMove.y/tileSize))) &&
		(sfevent.mouseMove.x < Scale)&&
		(sfevent.mouseMove.y < Scale)
		) {
		UpdateCurrentTile((int)trunc(sfevent.mouseMove.x/tileSize), (int)trunc(sfevent.mouseMove.y / tileSize));

		//std::cout << CurrentTileX << " = X\n";
		//std::cout << CurrentTileY << " = Y\n";
	}
}

void GraphMatrix::ClickOnTile()
{

	this->Grid->NextMove(CurrentTileX + 1, CurrentTileY + 1);
	tileoverhover.play();

}





void GraphMatrix::UpdateCurrentTile(int x, int y)
{
	this->CurrentTileX = x;
	this->CurrentTileY = y;
	
}
