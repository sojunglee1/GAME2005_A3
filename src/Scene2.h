#pragma once
#ifndef __SCENE_2__
#define __SCENE_2__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Detonator.h"
#include "Button.h"
#include "Label.h"
#include "Ball.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);


private:
	// IMGUI Function
	void GUI_Function();

	std::string m_guiTitle;

	glm::vec2 m_mousePosition;

	SDL_Rect brick;

	Ball* m_pBall;

};

#endif /* defined (__PLAY_SCENE__) */