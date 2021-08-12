#pragma once
#include "Object.h"

class Barrel :public SpriteObject
{
private:
	bool collided=false;
public:
	Barrel(sf::Texture&, sf::Vector2f);
	void update(float) override;
	bool isAlive() override;
	bool canCollide(sf::Vector2f pos);
};

class Item : public SpriteObject
{
private:
	bool collided = false;
public:
	Item(sf::Texture&, sf::Vector2f);
	void update(float) override;
	bool isAlive() override;
};