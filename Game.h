#pragma once
#include<SFML/Graphics.hpp>
constexpr auto scale = 1;

class Level_base;
class Object;
class Game
{
private:
	static Game* instance;
	sf::RenderWindow GameWindow;
	Level_base* level;
	Level_base* nextlevel;
	sf::Vector2f bulletPos ;
public:
	Game(unsigned int width, unsigned int height, const char* title);
		
	static void run();
	
	static void loadLevel(Level_base* level);

	static sf::Vector2f getMousePosition();
	static Game* getInstance();	
	static sf::Texture& getTexture(const std::string&);
	static const sf::RenderWindow& getWindow();
	static std::vector<Object*> getObjects(int tag);

	static void addObject(Object* object);
	static void setBulletPos(sf::Vector2f pos)
	{
		instance->bulletPos = pos;
	} 
	static const sf::Vector2f getBulletPos()
	{
		return instance->bulletPos;
	}

};

