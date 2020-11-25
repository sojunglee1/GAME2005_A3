#include "Ball.h"
#include "TextureManager.h"
#include "Brick.h"
#include "CollisionManager.h"
Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/Circle.png", "circle");

	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(700.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->mass = 1.0;
	setType(BALL);
	vfac = 0.75;
}

Ball::~Ball()
= default;

void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Ball::update()
{
	getRigidBody()->acceleration = glm::vec2(0, 9.8 * getRigidBody()->mass); // force = 9.8(acceleration) * mass

	float deltaTime = 2.0f / 60.0f;

	getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;

	if (getTransform()->position.x > 800 - getWidth())
	{
		getTransform()->position.x = 800 - getWidth();
		getRigidBody()->velocity.x *= -vfac; // how much energy is lost (when hit the window sides)
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position.x = 0;
		getRigidBody()->velocity.x *= -vfac; // how much energy is lost (when hit the window sides)
	}

	if (getTransform()->position.y > 600 - getHeight())
	{
		getTransform()->position.y = 600 - getHeight();
		getRigidBody()->velocity.y *= -vfac; // how much energy is lost (when hit the window top or bottom)
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position.y = 0;
		getRigidBody()->velocity.y *= -vfac; // how much energy is lost (when hit the window top or bottom)
	}
	if (CollisionManager::AABBCheck(GameObject* brick, Ball* ball)
	{

	}
}

void Ball::clean()
{
}
