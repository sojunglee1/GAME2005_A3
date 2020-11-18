#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "enemy");

	auto size = TextureManager::Instance()->getTextureSize("enemy");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2
}