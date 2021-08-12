#pragma once
#include "Object.h"
#include <vector>
struct TileInfo
{
public:
	sf::Texture& texture;
	bool colladible;
public:
	TileInfo(sf::Texture& texture, bool colladible=false)
		:texture(texture),colladible(colladible) {}
};
struct Tile
{
private:
	TileInfo* tileInfo;
	sf::Sprite sprite;
public:
	Tile(TileInfo* info, sf::Vector2f pos)
		:tileInfo(info), sprite(info->texture)
	{
		sprite.setPosition(pos);
		sprite.setScale(scale, scale);
	}
	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
	const TileInfo* getInfo()
	{
		return tileInfo;
	}
};

class TileObject
	:public Object
{
public:
	std::vector<TileInfo>tileset;
	std::vector<std::vector<Tile>> tilemap;
public:
	TileObject(std::vector<TileInfo> tileset, std::vector<std::vector<size_t>> tilemapInfo)
		:tileset(tileset) 
	{
		sf::Vector2u size = tileset[0].texture.getSize();
		size.x *= scale;
		size.y *= scale;

		for (size_t i = 0; i < tilemapInfo.size(); i++)
		{
			std::vector<Tile> col;
			for (size_t j = 0; j < tilemapInfo[i].size(); j++)
			{
				sf::Vector2f pos(j*size.x, i*size.y);
				col.push_back(Tile(&this->tileset[tilemapInfo[i][j]], pos));
			}
			tilemap.push_back(col);
		}
	}
	void render(sf::RenderWindow& window,float deltaTime) override
	{
		for (auto& row : tilemap)
			for (auto& tile : row)
				tile.render(window);
		tilemap[0][0].render(window);
	}
	bool canCollide(sf::Vector2f pos)
	{
		sf::Vector2u size = tileset[0].texture.getSize();
		size.x *= scale;
		size.y *= scale;
		int i = pos.x / size.x;
		int j = pos.y / size.y;
		if (j >= 0 && j < tilemap.size() && i >= 0 && i < tilemap[j].size())
			return tilemap[j][i].getInfo()->colladible;
		else
			return false;
	}

};
