#pragma once
#ifndef __SCENE_1__
#define __SCENE_1__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Detonator.h"
#include "Button.h"
#include "Label.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

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