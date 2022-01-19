#include "ObstacleManager.h"
#include "ObstaclePipes.h"

ObstacleManager::ObstacleManager()
{
	xOffset = SCREEN_WIDTH / 3;

	for (int i = 0; i < 5; i++)
	{
		pipes[i] = new ObstaclePipes();
	}
	isCollided = false;
	init();
	f = 0;
	l = 4;
}

void ObstacleManager::init()
{
	
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			pipes[i]->position.x = SCREEN_WIDTH + 100.f;
			
		}
		else
		{
			pipes[i]->position.x = pipes[i - 1]->position.x + xOffset;
			
		}
		srand((unsigned)(i));
		pipes[i]->position.y = ((rand() % 8) * (SCREEN_HEIGHT * 3 / 8 / 10)) + (SCREEN_HEIGHT / 4);
		pipes[i]->resetPosition();
	}
}

void ObstacleManager::update(float dt)
{
	if (!isCollided)
	{
		if (pipes[f]->position.x < -100.f)
		{
			pipes[f]->position.x = pipes[l]->position.x + xOffset;
			l = f;
			f = (f + 1) % 5;

			srand((unsigned)time(&t));
			pipes[l]->position.y = ((rand() % 8) * (SCREEN_HEIGHT * 3 / 8 / 10)) + (SCREEN_HEIGHT / 4);
			pipes[l]->resetPosition();
			pipes[l]->isScoreUpdated = false;

		}
		for (int i = 0; i < 5; i++)
		{
			pipes[i]->update(dt);
		}
	}
	
}

void ObstacleManager::reset()
{
	isCollided = false;
	for (int i = 0; i < 5; i++)
	{
		pipes[i]->reset();
	}
	init();
	f = 0;
	l = 4;
}
