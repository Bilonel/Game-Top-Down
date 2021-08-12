#pragma once
#include "Game.h"

class Object
{
public:
	int tag;
	sf::Vector2f bulletPos;

	Object(int tag=0) :tag(tag), bulletPos(-111, -111) {}
	virtual void update(float deltaTime) {}
	virtual void render(sf::RenderWindow& window,float deltaTime) {}
	virtual bool isAlive()  {return true; }

};

class SpriteObject : public Object
{
public:
	sf::Sprite sprite;
	

	SpriteObject(sf::Texture& texture, int tag=0) :Object(tag), sprite(texture) {}

	virtual void render(sf::RenderWindow& window,float deltTime) { window.draw(sprite);}
};
