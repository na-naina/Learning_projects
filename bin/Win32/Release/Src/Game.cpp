#include "Game.h"
#include <iostream>

void Game::initWindow()
{
	this->window = new sf::RenderWindow(*windowSize, "NxN");
    this->window->setFramerateLimit(120);
}

void Game::initGamegrid()
{
    gamesession = new GameSession(W, H, this->mainMenu->GetGridSize(), this->mainMenu->GetWinCondition(), this->mainMenu->GetPlayerNumber());
}


Game::Game()
{
    
    this->windowSize = new sf::VideoMode(600, 600);
    this->initWindow();
    
}

Game::Game(float Width, float Height)
    : State(0)
{
    W = Width;
    H = Height;
    
    mainMenu = new TitleScreen(Width, Height);


    this->windowSize = new sf::VideoMode(Width, Height);
    this->initWindow();

}

Game::~Game()
{
	delete this->window;
    delete this->windowSize;
    delete this->gamesession;
    delete this->mainMenu;
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();

    system("cls");

}



void Game::updateSFMLEvents()
{

    while (this->window->pollEvent(this->sfEvent))
    {

        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();

        if (State == 1)
            this->gamesession->updateSFEvents(sfEvent);
    
        if (State == 0)
            this->mainMenu->updateSFEvents(sfEvent);
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (State == 1) {
        this->gamesession->update();
    }

    if (this->mainMenu->isEnded && State == 0) {
        State = 1;
        initGamegrid();
    }

}

void Game::render()
{

    this->window->clear();

    if (State == 1) {
        this->gamesession->render(window);
    }

    if (State == 0) {
        this->mainMenu->render(window);
    }

    this->window->display();

}

void Game::run()
{
    while (this->window->isOpen())
    {
            this->updateDt();
            this->update();
            this->render(); 
    }
}
