#pragma once
#include "Game.h"
class ObstaclePipes
{
public:
	ObstaclePipes();

public:
	
	sf::Sprite pipe1;
	float scoreVertex;
	sf::Texture spriteTexture;
	sf::Sprite pipe2;
	sf::Vector2f position;
	float speed;
	float yOffset;

	bool isScoreUpdated;

	void update(float dt);

	void resetPosition();

	bool checkCollision(class Bird* const bird);

	bool updateScore(class Bird* const bird);

	void reset();
};

