#define _USE_MATH_DEFINES

#include <cmath>

#include "Enemy.h"
#include "Level.h"
#include "Tilemap.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>

Enemy::Enemy(sf::Texture & texture, TileObject * tilemap, sf::Vector2f pos,float speedX,float speedY)
	:SpriteObject(texture,Tag::Tag_enemy),cooldown(0.0f),map(tilemap),
	angleWander(1.571),pos(pos), isReel(0),speedX(speedX), speedY(speedY)
{
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(this->pos);
	sprite.setScale(scale, scale);
}

void Enemy::update(float deltaTime)
{
	std::vector<Object*> bullets = Game::getObjects(Tag::Tag_player_bullet);
	std::vector<Object*> player = Game::getObjects(Tag::Tag_player);
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
				Animation* animExplosionEnemy = new	Animation(Game::getTexture("explosion"), 8, 0.05f);
				animExplosionEnemy->sprite.setPosition(sprite.getPosition());
				animExplosionEnemy->sprite.setScale(0.5, 0.5);
				Game::addObject(animExplosionEnemy);
			}}
	}
	

	auto moveIfcan = [&](float dx, float dy,int a=1)
	{
		if (holdingTime > 0)
		{
			if( ((holdingTime*2)-(int)(holdingTime*2)) < deltaTime*1.2)
				sprite.setRotation(sprite.getRotation()+180);
			holdingTime -= deltaTime;
			std::cout << deltaTime << std::endl;
		}
		else
		{
			sf::Vector2f nextPosX = sprite.getPosition() + sf::Vector2f(dx, 0);
			sf::Vector2f nextPosY = sprite.getPosition() + sf::Vector2f(0, dy);
			flagX = !map->canCollide(nextPosX);
			flagY = !map->canCollide(nextPosY);

			if (flagX && flagY)
			{
				sprite.move(dx, dy);
				sprite.setRotation(std::atan2f(dy*a, dx*a) * 180 / (float)M_PI);
			}

			else if (flagX)
			{
				dx = sqrt(dx*dx + dy * dy)* dx / abs(dx);
				dy = 0;
				sprite.move(dx, dy);
				sprite.setRotation(std::atan2f(dy*a, dx*a) * 180 / (float)M_PI);
			}
			else if (flagY)
			{
				dx = 0;
				dy = sqrt(dx*dx + dy * dy)* dy / abs(dy);
				sprite.move(dx, dy);
				sprite.setRotation(std::atan2f(dy*a, dx*a) * 180 / (float)M_PI);
			}
		}
	};

	for (auto& it : player)
	{
		Player* player = dynamic_cast<Player*>(it);		
		sf::Vector2f diff = player->sprite.getPosition() - sprite.getPosition();
		float distance = sqrt(diff.x*diff.x + (diff.y*diff.y));

		sf::Vector2u size = sprite.getTexture()->getSize();
		sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin() - sf::Vector2f(size.x/4,size.y/4), sf::Vector2f(size.x*1.5*scale, size.y*1.5*scale));
		if (collider.contains(player->getAnimPos()))
			health -= 10;
		if (isSeen(diff,distance))
		{
			diff = (diff / distance)*float(200)*deltaTime;

			if (distance > 100)
				moveIfcan(diff.x, diff.y);
			else if (distance < 90)
				moveIfcan(-diff.x, -diff.y,-1);

			if (cooldown < 0)
			{
				SpriteObject* bullet = new Bullet(Game::getTexture("bullet"), map, Tag::Tag_enemy_bullet);
				Game::addObject(bullet);
				bullet->sprite.setPosition(sprite.getPosition());
				Game::setBulletPos(sprite.getPosition());
				bullet->sprite.setRotation(sprite.getRotation());
				cooldown = 1.5f;
			}
			cooldown -= deltaTime;
			lastSeenPoint = player->sprite.getPosition();
			isReel = 1;
		}
		else if (sqrt((lastSeenPoint - sprite.getPosition()).x*(lastSeenPoint - sprite.getPosition()).x + (lastSeenPoint - sprite.getPosition()).y*(lastSeenPoint - sprite.getPosition()).y) > 5 && isReel)
		{
			float angle = std::atan2f((lastSeenPoint - sprite.getPosition()).y, (lastSeenPoint - sprite.getPosition()).x);
			float dx = 200 * deltaTime*cos(angle);
			float dy = 200 * deltaTime*sin(angle);
			moveIfcan(dx, dy);
			if(sqrt((lastSeenPoint - sprite.getPosition()).x*(lastSeenPoint - sprite.getPosition()).x + (lastSeenPoint - sprite.getPosition()).y*(lastSeenPoint - sprite.getPosition()).y) < 5)
				holdingTime=5.0f;
		}
		else if(sqrt((pos - sprite.getPosition()).x*(pos - sprite.getPosition()).x + (pos - sprite.getPosition()).y*(pos - sprite.getPosition()).y) > 5)
		{
			float angle = std::atan2f((pos - sprite.getPosition()).y, (pos - sprite.getPosition()).x);
			float dx = 200 * deltaTime*cos(angle);
			float dy = 200 * deltaTime*sin(angle);
			moveIfcan(dx, dy);
			lastSeenPoint = sprite.getPosition();
			isReel = 0;
		}
		else
		{
			angleWander += 0.0007;
			float dx = speedX * deltaTime*cos(angleWander);
			float dy = speedY * deltaTime*sin(angleWander);
			moveIfcan(dx, dy);
			pos = sprite.getPosition();
		}				
	}	
}

bool Enemy::isSeen(sf::Vector2f diff,float dist)
{
	bool flag = 1;
	if (dist < 500)
	{
		float angle = std::atan2f(diff.y, diff.x);
		float sight = abs(angle*180.0f / (float)M_PI - sprite.getRotation());
		if (sight>=250 || sight<=110)
		{	
			diff = (diff / dist) * ((float)63.9) ;
			int i = sprite.getPosition().x ;
			int	j = sprite.getPosition().y ;

			for(int t=0;t<=dist/63.9;t++)
			{
				

				if (map->canCollide(sf::Vector2f(i, j)))
					flag = false;
				i += diff.x;
				j += diff.y;
			}
			if (flag)
				return true;
		}
	}
	if ( bulletPos != sf::Vector2f(-111,-111))
	{
		lastSeenPoint = bulletPos;
		bulletPos=sf::Vector2f(-111, -111);
		isReel = 1;
	}
		return false;
}


bool Enemy::isAlive()
{
	return health >0;
}
