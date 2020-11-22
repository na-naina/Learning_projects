#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
	Game game(900.f, 900.f);
	
	game.run();

	return 0;
}