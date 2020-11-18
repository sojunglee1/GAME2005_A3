#pragma once
#ifndef __SCENE_2__
#define __SCENE_2__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Detonator.h"
#include "Button.h"
#include "Label.h"

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

private:
	// IMGUI Function
	void GUI_Function();

	std::string m_guiTitle;

	glm::vec2 m_mousePosition;
};

#endif /* defined (__PLAY_SCENE__) */