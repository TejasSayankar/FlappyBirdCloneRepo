#include "Game.h"
#include "Bird.h"
#include "ObstacleManager.h"
#include "ObstaclePipes.h"

Game::Game()
{
	gameInitialization();
}

void Game::gameInitialization()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
	window.setFramerateLimit(60);
	bird = new Bird();
	
	obsManager = new ObstacleManager();
	bgTexture.loadFromFile("Assets/sprites/background-night.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(sf::Vector2f(1.4f,1.4f));

	groundTexture.loadFromFile("Assets/sprites/base.png");
	groundSprite.setTexture(groundTexture);
	groundSprite.setPosition(sf::Vector2f(0.f, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4)));
	groundSprite.setScale(sf::Vector2f(1.65f, 1.65f));

	startTexture.loadFromFile("Assets/sprites/message.png");
	startSprite.setTexture(startTexture);
	startSprite.setScale(2.f, 2.f);
	startSprite.setOrigin(startSprite.getGlobalBounds().width / 2 / 2, startSprite.getGlobalBounds().height / 2 / 2);
	startSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	
	gameOverTexture.loadFromFile("Assets/sprites/gameover.png");
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setScale(2.f, 2.f);
	gameOverSprite.setOrigin(startSprite.getGlobalBounds().width / 2 / 2, startSprite.getGlobalBounds().height / 2);
	gameOverSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT));

	
	hitSoundBuffer.loadFromFile("Assets/audio/Hit.wav");
	hitSound.setBuffer(hitSoundBuffer);

	pointSoundBuffer.loadFromFile("Assets/audio/Point.wav");
	pointSound.setBuffer(pointSoundBuffer);


	font.loadFromFile("Assets/fonts/FlappyFont.ttf");
	
	score = 0;
	addText(scoreText, sf::String(std::to_string(score)), sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8), 60.f, sf::Color::White);

	isPlaying = false;
	isGameOver = false;

	addText(playText, "Press Space to Play", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3), 40.f, sf::Color::Red);
}

void Game::gameLoop()
{
	while (window.isOpen()) 
	{
		deltaTime = (deltaClock.restart()).asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (!isPlaying)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						isPlaying = true;
					}
				}
			}
			if (isGameOver)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						reset();
						addText(playText, "Press Space to Play", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + SCREEN_HEIGHT / 3), 40.f, sf::Color::Red);
					}
				}
			}
		}
		window.clear();
		update();
		window.display();
	}
}

void Game::update()
{
	window.draw(bgSprite);
	for (int i = 0; i < 5; i++)
	{
		window.draw(obsManager->pipes[i]->pipe1);
		window.draw(obsManager->pipes[i]->pipe2);
	}

	window.draw(groundSprite);
	window.draw(bird->birdSprite);
	if (isPlaying)
	{
		if (isGameOver)
		{
			window.draw(gameOverSprite);
			window.draw(playText);
		}
		for (int i = 0; i < 5; i++)
		{
			if (!obsManager->isCollided)
			{
				if (obsManager->pipes[i]->checkCollision(bird))
				{
					obsManager->isCollided = true;
					isGameOver = true;

					addText(playText, "Press Space to Continue", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3), 40.f, sf::Color::Red);
					hitSound.play();
				}
				if (obsManager->pipes[i]->updateScore(bird))
				{

					score++;
					addText(scoreText, sf::String(std::to_string(score)), sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8), 60.f, sf::Color::White);

					pointSound.play();
				}
			}
			
		}
		if (!bird->isCollided)
		{
			if (checkCollision(bird))
			{
				bird->isCollided = true;
				obsManager->isCollided = true;
				isGameOver = true;
				hitSound.play();
				addText(playText, "Press Space to Continue", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 3), 40.f, sf::Color::Red);

			}
		}
		

		
		bird->update(deltaTime);
		obsManager->update(deltaTime);
		
		window.draw(scoreText);
	}
	else
	{
		window.draw(startSprite);
		window.draw(playText);
	}
	
}

bool Game::checkCollision(Bird* const bird)
{
	return groundSprite.getGlobalBounds().intersects(bird->birdSprite.getGlobalBounds());
}

void Game::addText(sf::Text& text, const sf::String& string, sf::Vector2f pos, int font_size, sf::Color color)
{
	text.setFont(font);
	text.setString(string);
	text.setCharacterSize(font_size);
	text.setFillColor(color);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
	text.setPosition(pos);
}

void Game::reset()
{
	score = 0;
	addText(scoreText, sf::String(std::to_string(score)), sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8), 60.f, sf::Color::White);

	isPlaying = false;
	isGameOver = false;
	bird->reset();
	obsManager->reset();
}
