#pragma once
#include "Game.h"
//#include <SFML/Graphics.hpp>
class Bird
{
public:
	Bird();

public:

	sf::Sprite birdSprite;
	sf::Texture birdTexture[4];
	sf::Clock clock;

	//sf::RectangleShape rectShape;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float gravity;
	float jumpHeight;
	int textureCount;
	float speed;
	
	sf::SoundBuffer flySoundBuffer;

	sf::Sound flySound;

	bool isCollided;
	void update(float dt);
	void jump();

	void reset();
};

