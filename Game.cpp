#include "Game.h"
#include "level_base.h"
#include "Level.h"
#include<chrono>
#include<SFML/Graphics.hpp>

Game* Game::instance = nullptr;

Game::Game(unsigned int width, unsigned int height, const char * title)
	:GameWindow(sf::VideoMode(width, height), title), level(nullptr), nextlevel(nullptr),
	bulletPos(-111,-111)
{
	instance = this;
	instance->loadLevel(new Level());
}
void Game::run()
{
	float deltaTime;
	auto t1 = std::chrono::high_resolution_clock::now();
	while (instance->GameWindow.isOpen())
	{
		auto t2= std::chrono::high_resolution_clock::now();
		deltaTime = (std::chrono::duration<float>(t2 - t1)).count();
		t1 = t2;
		
		sf::Event event;
		while (instance->GameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				instance->GameWindow.close();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				instance->GameWindow.close();
		}

		if (instance->nextlevel)
		{
			delete instance->level;
			instance->level= instance->nextlevel;
			instance->nextlevel = nullptr;
		}
		instance->level->update(deltaTime);
		instance->GameWindow.clear(sf::Color (205,205,205));
		instance->level->render(instance->GameWindow,deltaTime);
		instance->GameWindow.display();
	}
}
void Game::loadLevel(Level_base * level)
{
	instance->nextlevel = level;
}

sf::Vector2f Game::getMousePosition()
{
	return sf::Vector2f(sf::Mouse::getPosition(instance->GameWindow));
}


Game * Game::getInstance()
{
	return instance;
}


sf::Texture & Game::getTexture(const std::string & str)
{
	return instance->level->getTexture(str);
}

const sf::RenderWindow& Game::getWindow()
{
	return instance->GameWindow;
}

std::vector<Object*> Game::getObjects(int tag)
{
	return instance->level->getObjects(tag);
}

void Game::addObject(Object * object)
{
	instance->level->addObject(object);
}
