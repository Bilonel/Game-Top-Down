#include "Barrel.h"
#include "Level.h"
#include "Bullet.h"
#include "Player.h"

Barrel::Barrel(sf::Texture & texture, sf::Vector2f pos)
	:SpriteObject(texture,Tag::Tag_barrel)
{
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
}

void Barrel::update(float deltaTime)
{
	std::vector<Object*> bullets = Game::getObjects(Tag::Tag_player_bullet);
	std::vector<Object*> enemy_bullets = Game::getObjects(Tag::Tag_enemy_bullet);
	std::vector<Object*> players = Game::getObjects(Tag::Tag_player);

	for (auto& it : players)
	{
		Player* player = dynamic_cast<Player*>(it);
		if(player)
		{
			sf::Vector2u size = sprite.getTexture()->getSize();
			sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin() - sf::Vector2f(size.x / 4, size.y / 4), sf::Vector2f(size.x*1.5*scale, size.y*1.5*scale));
			if (collider.contains(player->getAnimPos()))
				collided = true;
		}
	}
	
	
	for (auto& go : enemy_bullets)
		bullets.push_back(go);
	
	for (auto& it : bullets)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(it);
		if (bullet)
		{
			sf::Vector2u size = sprite.getTexture()->getSize();
			sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin(), sf::Vector2f(size.x*scale, size.y*scale));
			if (collider.contains(bullet->sprite.getPosition()))
			{
				collided = true;
				bullet->health--;

				Animation* animExplosionBarrel = new	Animation(Game::getTexture("explosion"), 8, 0.05f);
				animExplosionBarrel->sprite.setPosition(sprite.getPosition());
				Game::addObject(animExplosionBarrel);
			}
		}
	}
	
}

bool Barrel::isAlive()
{
	return !collided;
}

bool Barrel::canCollide(sf::Vector2f pos)
{
	sf::Vector2u size = sprite.getTexture()->getSize();
	sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin(), sf::Vector2f(size.x*scale, size.y*scale));
	if (collider.contains(pos))
		return true;
	else
		return false;
}

Item::Item(sf::Texture & texture, sf::Vector2f pos)
	:SpriteObject(texture)
{
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
}

void Item::update(float deltaTime)
{
	std::vector<Object*> player = Game::getObjects(Tag::Tag_player);

	for (auto& it : player)
	{
		Player* player = dynamic_cast<Player*>(it);
		if (player)
		{
			sf::Vector2u size = sprite.getTexture()->getSize();
			sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin(), sf::Vector2f(size.x*scale, size.y*scale));
			if (collider.contains(player->sprite.getPosition()))
			{
				collided = true;
				player->sprite.setTexture(Game::getTexture("player"));
				player->setWeapon(3);
			}
		}
	}
}

bool Item::isAlive()
{
	return !collided;
}

