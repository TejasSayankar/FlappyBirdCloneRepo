#include "ObstaclePipes.h"
#include "Bird.h"

ObstaclePipes::ObstaclePipes()
{
	spriteTexture.loadFromFile("Assets/sprites/pipe-red.png");
	pipe1.setTexture(spriteTexture);
	pipe2.setTexture(spriteTexture);
	yOffset = SCREEN_HEIGHT / 8;
	speed = 4.f;
	scoreVertex = position.x + 30.f;
	isScoreUpdated = false;
}

void ObstaclePipes::update(float dt)
{

	speed += dt * 0.03;
	position.x -= speed;
	scoreVertex = position.x + 30.f;
	resetPosition();
	
}

void ObstaclePipes::resetPosition()
{
	scoreVertex = position.x + 30.f;
	pipe1.setPosition(sf::Vector2f(position.x, position.y + yOffset));
	pipe2.setPosition(sf::Vector2f(position.x, position.y - yOffset));
	pipe2.setScale(sf::Vector2f(1, -1)); 
}

bool ObstaclePipes::checkCollision(Bird* const bird)
{
	return pipe1.getGlobalBounds().intersects(bird->birdSprite.getGlobalBounds()) || pipe2.getGlobalBounds().intersects(bird->birdSprite.getGlobalBounds());
}

bool ObstaclePipes::updateScore(Bird* const bird)
{
	if (!isScoreUpdated && bird->birdSprite.getPosition().x >= scoreVertex) 
	{
		isScoreUpdated = true;
		return true;
	}
	return false;
}

void ObstaclePipes::reset()
{
	speed = 4.f;
	scoreVertex = position.x + 30.f;
	isScoreUpdated = false;
}


