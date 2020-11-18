#include "BulletPool.h"

BulletPool::BulletPool(int size)
{
	for (int i = 0; i < size; i++)
	{
		Bullet* bullet = new Bullet();
		inactiveBull.push_back(bullet);
		allBull.push_back(bullet);
	}

	std::cout << "Bullet Pool created with size " << size << std::endl;
}

BulletPool::~BulletPool() = default;

Bullet* BulletPool::Spawn()
{
	Bullet* bullet = NULL;
	if (inactiveBull.size() > 0)
	{
		bullet = inactiveBull.back();
		bullet->Reset();
		bullet->active = true;
		inactiveBull.pop_back();
		activeBull.push_back(bullet);
		std::cout << "SPAWNED" << std::endl;
		std::cout << "Active Count: " << std::to_string(activeBull.size()) << std::endl;

	}
	else {
		std::cout << "ERROR: Max bullets spawned." << std::endl;
	}
	return bullet;
}

void BulletPool::Despawn(Bullet* bullet)
{
	bullet->Reset();
	inactiveBull.push_back(bullet);

	for (std::vector<Bullet*>::iterator myiter = activeBull.begin(); myiter != activeBull.end(); myiter++)
	{
		if (*myiter == bullet)
		{
			activeBull.erase(myiter);
			std::cout << "DESPAWNED" << std::endl;
			std::cout << "Active Count: " << std::to_string(activeBull.size()) << std::endl;
			return;
		}
	}

}