#include "Brick.h"
#include "EventManager.h"
#include "TextureManager.h"
Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/brick.png", "brick");

	auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(50.0f, 50.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->mass = 1.0;
	setType(BALL);
}

Brick::~Brick()
= default;

void Brick::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}

void Brick::update()
{
	getTransform()->position.x = EventManager::Instance().getMousePosition().x;
	getTransform()->position.y = EventManager::Instance().getMousePosition().y;
}

void Brick::clean()
{
}
