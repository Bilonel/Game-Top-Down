#pragma once

#include "Game.h"
#include "Object.h"
#include "Animation.h"

class TileObject;
class Player:public SpriteObject
{
private:
	TileObject* map;
	float cooldown;
	int speed;
	int health;
	Animation* animAttack;
	bool animated;
	int currentLevel;
	bool moveFlag = 1;
	int weapon = 0;

	sf::RectangleShape healthBar;
	sf::RectangleShape healthBar2;
	sf::Sprite UIsprite;
	sf::Texture UItexture;
public:

	Player(sf::Texture& texture, TileObject* tilemap,int, int currentLevel);
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window, float deltaTime) override;
	bool isAlive();
	sf::Vector2f getAnimPos();
	int getHealth()
	{
		return health;
	}
	void setWeapon(int x)
	{
		weapon = x;
	}
};

