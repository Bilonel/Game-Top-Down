#define _USE_MATH_DEFINES
#include <cmath>
#include "Level.h"
#include "Player.h"
#include "Bullet.h"
#include "Tilemap.h"
#include "Level2.h"
#include "Barrel.h"

Player::Player(sf::Texture& texture, TileObject* tilemap,int wep,int currentLevel)
	:SpriteObject(texture,Tag::Tag_player), cooldown(0.0f), speed(150),map(tilemap),health(8), animated(0),
	weapon(wep),currentLevel(currentLevel)
{
	sprite.setScale(scale, scale);
	sprite.setOrigin(texture.getSize().x / 2 - 12, texture.getSize().y / 2);
	sprite.setPosition(100, 150);

	healthBar.setFillColor(sf::Color(205, 0, 0));
	healthBar2.setFillColor(sf::Color::Transparent);
	healthBar2.setOutlineThickness(3);
	healthBar2.setOutlineColor(sf::Color::Black);
	healthBar.setPosition(sf::Vector2f(Game::getWindow().getSize().x - 180, 38));
	healthBar2.setPosition(sf::Vector2f(Game::getWindow().getSize().x - 180, 38));
	healthBar.setSize(sf::Vector2f(160, 30));
	healthBar2.setSize(sf::Vector2f(160, 30));
	UIsprite.setPosition(sf::Vector2f(Game::getWindow().getSize().x - 260, 20));
}

void Player::update(float deltaTime)
{

	auto moveIfcan = [&](float dx, float dy)
	{
		std::vector<Object*> barrels = Game::getObjects(Tag::Tag_barrel);

		sf::Vector2u size = Game::getWindow().getSize();
		sf::Vector2f nextPos = sprite.getPosition() + sf::Vector2f(dx, dy);
		for (auto& it : barrels)
		{
			Barrel* barrel = dynamic_cast<Barrel*>(it);
			if(moveFlag)
				moveFlag = !(barrel->canCollide(nextPos));
		}
		if (moveFlag &&!(map->canCollide(nextPos)) && (nextPos.x >= 0 && nextPos.x <= size.x) && (nextPos.y >= 0 && nextPos.y <= size.y))
			sprite.setPosition(nextPos);
		moveFlag = 1;
	};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		speed = 400;
	else
		speed = 250;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		moveIfcan(-speed * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		moveIfcan(speed * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		moveIfcan(0, -speed * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		moveIfcan(0, speed * deltaTime);
	sf::Vector2f lookDirection = Game::getMousePosition() - sprite.getPosition();
	sprite.setRotation(std::atan2f(lookDirection.y, lookDirection.x) * 180 / (float)(M_PI)) ;
	if(sprite.getPosition().y + 16 > Game::getWindow().getSize().y)
		switch (currentLevel)
		{
		case 1: Game::getInstance()->loadLevel(new Level2());
			break;
		case 2: Game::getInstance()->loadLevel(new Level2());
			break;
		}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown < 0)
	{
		if (weapon == 3)
		{
			SpriteObject* newBullet = new Bullet(Game::getTexture("bullet"), map, Tag::Tag_player_bullet);
			Game::addObject(newBullet);
			newBullet->sprite.setPosition(sprite.getPosition());
			newBullet->sprite.setRotation(sprite.getRotation());
			cooldown = 0.35f;
			std::vector<Object*> enemies = Game::getObjects(Tag::Tag_enemy);
			for (auto& it : enemies)
			{
				it->bulletPos = sprite.getPosition();
			}
		}
		else if (weapon == 1 && cooldown < 0)
		{
			animAttack = new Animation(Game::getTexture("anim-knife"), 2, 0.15f,Tag::Tag_knife);
			
			Game::addObject(animAttack);
			animated = 1;
			cooldown = 0.3f;
		}
	}
	if (cooldown < 0)
		animated = 0;
	if (animated)
	{
		animAttack->sprite.setPosition(sprite.getPosition());
		animAttack->sprite.setRotation(sprite.getRotation());
	}
	
	cooldown -= deltaTime;

	std::vector<Object*> bullets = Game::getObjects(Tag::Tag_enemy_bullet);
	for (auto& it : bullets)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(it);
		if (bullet)
		{
			sf::Vector2u size = sprite.getTexture()->getSize();
			sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin(), sf::Vector2f(size.x*scale, size.y*scale));
			if (collider.contains(bullet->sprite.getPosition()))
			{
				bullet->health--;
				health--;
				Animation* animExplosionPlayer = new	Animation(Game::getTexture("explosion"), 8, 0.05f);
				animExplosionPlayer->sprite.setPosition(sprite.getPosition());
				animExplosionPlayer->sprite.setScale(0.5, 0.5);
				Game::addObject(animExplosionPlayer);
			}
		}
		
	}
	healthBar.setSize(sf::Vector2f(20 * health, 30));
	switch (weapon)
	{
	case 1: UItexture.loadFromFile("res/knife.png");
		UIsprite.setScale(2, 2);
		UIsprite.setTexture(UItexture);
		break;
	case 3: UItexture.loadFromFile("res/gunBar.png");
		UIsprite.setScale(2, 2);
		UIsprite.setTexture(UItexture);
		break;
	}
	
}
void Player::render(sf::RenderWindow& window, float deltaTime)
{
	if (!animated )
	{
		window.draw(sprite);
	}
	window.draw(healthBar);
	window.draw(healthBar2);
	window.draw(UIsprite);
}

bool Player::isAlive()
{
	return health > 0;
}

sf::Vector2f Player::getAnimPos()
{
	if (animated)
		return sf::Vector2f(animAttack->sprite.getPosition().x +15 , animAttack->sprite.getPosition().y);
	else
		return sf::Vector2f(-111, -111);
}

