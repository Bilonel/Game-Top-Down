#include "Level_base.h"

#include <vector>
#include <string>


void Level_base::update(float deltaTime)
{
	for (auto& it : additionList)
		objects.push_back(it);
	additionList.clear();
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->isAlive())
		{
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}
	for (auto& it : objects)
		it->update(deltaTime);
}

void Level_base::render(sf::RenderWindow & window, float deltaTime)
{
	for (auto& it : objects)
		it->render(window, deltaTime);
}

Level_base::~Level_base()
{
	for (auto& it : additionList)
		delete it;
	for (auto& it : objects)
		delete it;
}

void Level_base::addObject(Object * object)
{
	additionList.push_back(object);
}

sf::Texture & Level_base::getTexture(const std::string & str)
{
	return textures[str];
}

std::vector<Object*> Level_base::getObjects(int tag)
{
	std::vector<Object*> temp;
	for (auto& it : objects)
		if (it->tag == tag)
			temp.push_back(it);
	return temp;
}
