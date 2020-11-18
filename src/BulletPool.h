#pragma once

#include "Bullet.h"
#include <iostream>

class BulletPool
{
public:

	BulletPool(int);
	~BulletPool();

	int size;
	int index = 0;

	Bullet* Spawn();
	void Despawn(Bullet*);

	std::vector<Bullet*> allBull;

private:

	std::vector<Bullet*> activeBull;
	std::vector<Bullet*> inactiveBull;
};
