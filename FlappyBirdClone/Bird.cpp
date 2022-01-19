#include<iostream>
#include"Game.h"
#include "Bird.h"

Bird::Bird()
{
	velocity = sf::Vector2f(0, 1);
	gravity = 9.18f;
	jumpHeight = 7.f;
	position = sf::Vector2f(200, 300);
	birdTexture[0].loadFromFile("Assets/sprites/bluebird-downflap.png");
	birdTexture[1].loadFromFile("Assets/sprites/bluebird-midflap.png");
	birdTexture[2].loadFromFile("Assets/sprites/bluebird-upflap.png");
	birdTexture[3].loadFromFile("Assets/sprites/bluebird-midflap.png");
	
	flySoundBuffer.loadFromFile("Assets/audio/Wing.wav");
	flySound.setBuffer(flySoundBuffer);

	birdSprite.setScale(sf::Vector2f(1.5f, 1.5f));
	birdSprite.setOrigin(birdSprite.getGlobalBounds().width / 2, birdSprite.getGlobalBounds().height / 2);
	birdSprite.setPosition(position);
	speed = 2.f;
	isCollided = false;
	clock.restart();
	textureCount = 0;
	birdSprite.setTexture(birdTexture[textureCount]);
}
 
void Bird::update(float dt)
{
	if (!isCollided)
	{
		if (clock.getElapsedTime().asSeconds() > 0.2f)
		{
			if (textureCount < 3)
			{
				textureCount++;
			}
			else
			{
				textureCount = 0;
			}
			birdSprite.setTexture(birdTexture[textureCount]);
			clock.restart();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jump();
		}
		velocity.y += (/*(abs(velocity.y))**/ gravity * dt * speed);
		position.y += velocity.y;
		birdSprite.setPosition(position);
		
	}
	
}
 


void Bird::jump()
{
	flySound.play();
	velocity.y = -(jumpHeight);
}

void Bird::reset()
{
	velocity = sf::Vector2f(0, 1);
	gravity = 9.18f;
	jumpHeight = 7.f;
	position = sf::Vector2f(200, 300);
	birdSprite.setPosition(position);
	birdSprite.setRotation(0);
	//rectShape.setSize(sf::Vector2f(50, 50));
	//rectShape.setFillColor(sf::Color::Green);
	speed = 2.f;
	isCollided = false;
}
