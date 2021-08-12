#include "Level2.h"
#include "Player.h"
#include "Tilemap.h"
#include "Barrel.h"
#include "Enemy.h"

#include <vector>
Level2::Level2()
{
	textures["player"].loadFromFile("res/player.png");
	textures["playerKnife"].loadFromFile("res/player-knife.png");
	textures["enemy"].loadFromFile("res/enemy.png");

	textures["bullet"].loadFromFile("res/bullet.png");

	textures["floor"].loadFromFile("res/tile/floor.png");
	textures["floor-1"].loadFromFile("res/tile/floor2.png");
	textures["Wall-2"].loadFromFile("res/tile/Left_Right_Wall.png");
	textures["map"].loadFromFile("res/tile/map2.png");

	textures["barrel"].loadFromFile("res/tile/barrel.png");
	textures["explosion"].loadFromFile("res/explosion.png");
	textures["player-anim"].loadFromFile("res/player-anim.png");
	textures["anim-knife"].loadFromFile("res/anim-knife.png");
	textures["gun"].loadFromFile("res/gun.png");
	textures["gunBar"].loadFromFile("res/gunBar.png");
	textures["knifeBar"].loadFromFile("res/knife.png");
	textures["WellDone"].loadFromFile("res/WellDone.png");
	textures["GameOver"].loadFromFile("res/GameOver.png");

	std::vector<TileInfo> tileset{ TileInfo(textures["floor"]),TileInfo(textures["floor-1"]),TileInfo(textures["Wall-2"],true),TileInfo(textures["map"]) };
	std::vector<std::vector<size_t>> map
	{
		{3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,2,0,0,0,0,2,2,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,1,2,2},
	};
	TileObject* tilemap = new TileObject(tileset, map);
	objects.push_back(tilemap);
	objects.push_back(new Player(textures["playerKnife"], tilemap, 1,2));
	objects.push_back(new Enemy(textures["enemy"], tilemap, sf::Vector2f(850, 500), -150 * 0.4, -150 * 1.0));
	objects.push_back(new Enemy(textures["enemy"], tilemap, sf::Vector2f(224, 800), -150 * 1.4, 150 * 0.35));
	objects.push_back(new Enemy(textures["enemy"], tilemap, sf::Vector2f(975, 820), -150 * 0.6, -150 * 0.5));
	objects.push_back(new Item(textures["gun"], sf::Vector2f(6.5 * 64 * scale, 3.5 * 64 * scale)));
	objects.push_back(new Barrel(textures["barrel"], sf::Vector2f(6.5 * 64 * scale, 3.5 * 64 * scale)));
	objects.push_back(new Barrel(textures["barrel"], sf::Vector2f(4.5 * 64 * scale, 6.5 * 64 * scale)));
	objects.push_back(new Barrel(textures["barrel"], sf::Vector2f(10.5 * 64 * scale, 2.5 * 64 * scale)));
	objects.push_back(new Barrel(textures["barrel"], sf::Vector2f(8.5 * 64 * scale, 7.5 * 64 * scale)));
}