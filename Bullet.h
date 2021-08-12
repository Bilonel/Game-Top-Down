
#include "Object.h"
#include "Tilemap.h"
#include "Animation.h"

class Bullet :
	public SpriteObject
{
private:
	TileObject* map;
public:
	int health = 1;
public:
	Bullet(sf::Texture& texture, TileObject* tilemap,int tag)
		:SpriteObject(texture,tag),map(tilemap) {}
	void update(float deltaTime) override;
	bool isAlive() override;
};

