#pragma once
#include "ECS.h"

class PositionComponent : public Component
{
private:
	float xPos = 0.0f, yPos = 0.0f;
public:
	float x() { return xPos; }
	float y() { return yPos; }

	void setPos(float x, float y)
	{
		this->xPos = x;
		this->yPos = y;
	}

	void init() override
	{
		xPos = 0.0f;
		yPos = 0.0f;
	}

	void update() override
	{
		xPos += 1.0f;
		yPos += 1.0f;
	}

	void draw() override
	{

	}
};