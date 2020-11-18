#include "Scene1.h"
#include "Game.h"
#include "EventManager.h"
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

Scene1::Scene1()
{
	Scene1::start();
}
Scene1::~Scene1()
= default;

void Scene1::draw()
{
	//TextureManager::Instance()->draw("background", 0, 0);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Scene1::update()
{
	updateDisplayList();

	if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration)
	{
		SpawnBullet();
	}

	std::vector<Bullet*> activeBullets = m_pPool->allBull;
	for (std::vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); ++myiter)
	{
		Bullet* bullet = *myiter;
		if (bullet->active && bullet->getTransform()->position.y >= 650)
		{
			m_pPool->Despawn(bullet);
			break;
		}
	}
}

void Scene1::clean()
{
	removeAllChildren();
}

void Scene1::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->quit();
	}

	// moves Player
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D)){
		m_pPlayer->moveRight();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->moveDown();
	}
	else {
		m_pPlayer->stopMoving();
	}

	// changes scene
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0)){
		TheGame::Instance()->changeSceneState(START_SCENE);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1)){
		TheGame::Instance()->changeSceneState(SCENE_1);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2)){
		TheGame::Instance()->changeSceneState(SCENE_2);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3)){
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

}

void Scene1::start()
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	m_pPool = new BulletPool(10);
	for (std::vector<Bullet*>::iterator myiter = m_pPool->allBull.begin(); myiter != m_pPool->allBull.end(); ++myiter)
	{
		Bullet* bullet = *myiter;
		addChild(bullet);
	}
	bulletSpawnTimerStart = SDL_GetTicks();

}

void Scene1::SpawnBullet()
{
	Bullet* bullet = m_pPool->Spawn();
	if (bullet)
	{
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
	}

	bulletSpawnTimerStart = SDL_GetTicks();
}


void Scene1::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Fire"))
	{
	}

	else if (ImGui::Button("Reset"))
	{
	}

	//ImGui::Separator();
	//ImGui::SliderFloat("Range", &m_pPlaneSprite->getTransform()->position.x, 180.0f, 750.0f);

	ImGui::Separator();
	//std::cout << "Velocity: " << newVelocity.x << std::endl;
	//std::cout << "Acceleration: "<< newAcceleration.y << std::endl;

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
