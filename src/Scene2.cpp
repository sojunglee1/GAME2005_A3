#include "Scene2.h"
#include "Game.h"
#include "EventManager.h"
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "CollisionManager.h"
#include "Util.h"

Scene2::Scene2()
{
	Scene2::start();
}
Scene2::~Scene2()
= default;

void Scene2::draw()
{

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	//brick.x = EventManager::Instance().getMousePosition().x - brick.w / 2,
	//brick.y = EventManager::Instance().getMousePosition().y,
	//brick.w = 150,
	//brick.h = 15;

	/*SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_RenderFillRect(Renderer::Instance()->getRenderer(), &brick);*/


	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	drawDisplayList();
}

void Scene2::update()
{
	bounce();
	updateDisplayList();

}

void Scene2::clean()
{
	removeAllChildren();
}

void Scene2::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(SCENE_1);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(SCENE_2);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}	
}

void Scene2::start()
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	// Set GUI Title
	m_guiTitle = "Scene 2";

	m_pBall = new Ball();
	addChild(m_pBall);
	m_pBrick = new Brick();
	addChild(m_pBrick);
}

void Scene2::DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void Scene2::bounce()
{
	if (CollisionManager::AABBCheck(m_pBall, m_pBrick))
	{
		const float deltaTime = 1.0f / 60.f;
		std::cout << "ball hits brick" << std::endl;
		newVelocity = -m_pBall->getRigidBody()->velocity - m_pBrick->getRigidBody()->velocity;
		m_pBall->getRigidBody()->velocity = newVelocity;
		glm::vec2 newPos = m_pBall->getTransform()->position + (m_pBall->getRigidBody()->velocity * deltaTime);
		m_pBall->getTransform()->position = newPos;
		std::cout << "Brick's x velocity: " << m_pBrick->getRigidBody()->velocity.x << std::endl;
		std::cout << "Brick's y velocity: " << m_pBrick->getRigidBody()->velocity.y << std::endl;
	}
}

void Scene2::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	ImGui::Separator();

	ImGui::SliderFloat("Mass", &m_pBall->getRigidBody()->mass, 1.0f, 10.0f);

	ImGui::Separator();
	//std::cout << "Velocity: " << newVelocity.x << std::endl;
	//std::cout << "Acceleration: "<< newAcceleration.y << std::endl;

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

