#pragma once
#include "Game.h"
#include "Object.h"
#include <unordered_map>

class Level_base
{
protected:
	std::vector<Object*> objects;
	std::vector<Object*> additionList;
	std::unordered_map<std::string, sf::Texture> textures;
public:
	
	virtual void update(float deltaTime);
	virtual void render(sf::RenderWindow& window, float deltaTime);
	virtual ~Level_base();

	virtual void addObject(Object* object);
	virtual sf::Texture& getTexture(const std::string& str);
	std::vector<Object*> getObjects(int tag);
};
enum Tag
{
	Tag_object, Tag_player, Tag_enemy, Tag_player_bullet, Tag_enemy_bullet, Tag_barrel, Tag_knife
};
