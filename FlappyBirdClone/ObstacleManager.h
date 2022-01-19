#pragma once
#include "Game.h"
class ObstacleManager
{
public:
	ObstacleManager();

public:
	bool isCollided;
	time_t t;
	class ObstaclePipes* pipes[5];
	class ObstaclePipes* first;
	class ObstaclePipes* last;
	int f, l;
	void init();
	float xOffset;
	void update(float dt);
	void reset();
};

