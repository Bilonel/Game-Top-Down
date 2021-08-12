#pragma once
#include "Object.h"

class TileObject;
class Enemy :
	public SpriteObject
{
private:
	TileObject* map;
	float cooldown= 2.0f;
	float speedX;
	float speedY;
	int health = 3;
	sf::Vector2f lastSeenPoint;
	bool flagX = 0, flagY = 0;
	float angleWander;
	sf::Vector2f pos;
	bool isReel;
	float holdingTime = 0;
public:

	Enemy(sf::Texture& texture, TileObject* tilemap, sf::Vector2f pos ,float,float);
	void update(float deltaTime) override;
	bool isAlive() override;
	bool isSeen(sf::Vector2f,float);
};
