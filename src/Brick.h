#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "Sprite.h"

class Brick : public Sprite
{
public:
	Brick();
	~Brick();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters

private:

};

#endif /* defined (__BRICK__) */