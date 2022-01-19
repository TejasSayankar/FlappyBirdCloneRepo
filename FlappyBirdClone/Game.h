#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include<stdlib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
public:
	Game();

private:

	int score;

	float deltaTime;

	sf::RenderWindow window;
	sf::Clock deltaClock;

	sf::Sprite bgSprite;
	sf::Texture bgTexture;

	sf::Sprite groundSprite;
	sf::Texture groundTexture;

	sf::Sprite startSprite;
	sf::Texture startTexture;

	sf::Font font;

	class Bird* bird;

	class ObstacleManager* obsManager;

	sf::Text scoreText;

	sf::Text playText;

	bool isGameOver;

	sf::Sprite gameOverSprite;
	sf::Texture gameOverTexture;

	sf::SoundBuffer hitSoundBuffer;
	sf::Sound hitSound;

	sf::SoundBuffer pointSoundBuffer;
	sf::Sound pointSound;


	bool isPlaying;

public:
	void gameInitialization();
	void gameLoop();

	void update();

	bool checkCollision(class Bird* const bird);

	void addText(sf::Text& text, const sf::String& string, sf::Vector2f pos, int font_size, sf::Color color);

	void reset();
};

