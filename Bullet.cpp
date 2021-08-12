#define _USE_MATH_DEFINES

#include <cmath>
#include "Bullet.h"

void Bullet::update(float deltaTime)
{
	float dx = 800 * deltaTime*cos(sprite.getRotation()*(float)M_PI / 180);
	float dy = 800 * deltaTime*sin(sprite.getRotation()*(float)M_PI / 180);
	sprite.move(dx, dy);
	sprite.setScale(0.65, 0.65);
	if (map->canCollide(sprite.getPosition()))
	{
		Animation* animExplosion = new	Animation(Game::getTexture("explosion"), 8, 0.05f);
		animExplosion->sprite.setScale(0.5, 0.5);
		animExplosion->sprite.setPosition(sprite.getPosition());
		Game::addObject(animExplosion);
	}
}

bool Bullet::isAlive()
{
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2u size = Game::getWindow().getSize();
	return health > 0 && !(map->canCollide(pos)) && (pos.x >= 0 && pos.x <= size.x) && (pos.y >= 0 && pos.y <= size.y);
}
