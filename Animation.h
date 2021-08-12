#pragma once
#include "Object.h"

class Animation:public SpriteObject
{
private:
	int currentStep;
	float frameTime;
	float animTime;
	int frames;
	sf::IntRect frameRect;
	bool onlyOnce;
public:
	Animation(sf::Texture& texture, int frames, float animTime, bool onlyonce = true,int tag=0)
		:SpriteObject(texture,tag), frames(frames), animTime(animTime), frameTime(0), currentStep(0),
		onlyOnce(onlyonce),
		frameRect(sf::Vector2i(0,0),sf::Vector2i(texture.getSize().x / frames, texture.getSize().y ))
	{
		sprite.setTextureRect(frameRect);
		sprite.setOrigin(frameRect.width / 2, frameRect.height / 2);
	}
	void render(sf::RenderWindow& window, float deltaTime) override
	{
		if(frameTime>=animTime)
		{
			currentStep = (currentStep + 1) % (frames * 2);
			frameRect.left = (currentStep%frames) * frameRect.width;
			sprite.setTextureRect(frameRect);
			frameTime = 0;
		}
		frameTime += deltaTime;
		window.draw(sprite);
	}
	bool isAlive() override
	{
		if (onlyOnce)
			return currentStep < frames;
		else
			return true;
	}
};