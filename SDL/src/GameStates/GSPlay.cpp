#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
	printf("Huy doi tuong GSPLAY\n");
}


void GSPlay::Init()
{
	LoadCSV(s_pLevel);
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Map/map"+std::to_string(s_pLevel)+".jpg");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/closeButton.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, " ");
	button->SetSize(64, 64);
	button->Set2DPosition(SCREEN_WIDTH - button->GetWidth() - 10, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	cursorIcon = IMG_Load("Data/Textures/GUI/target.svg");
	customCursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
	SDL_FreeSurface(cursorIcon);
	SDL_SetCursor(customCursor);

	//Get data for m_Dynamic Map and make object

	// Add Player
	texture = ResourceManagers::GetInstance()->GetTexture("MainCharacter/3 Dude_Monster/Dude_Monster_Run_6.png");
	m_player = std::make_shared<Player>(texture, 1, 6, 1, 0.15f);
	m_player->SetSize(64, 64);
	m_player->Set2DPosition(240, 400);
	//Camera::GetInstance()->SetTarget(obj);
	//m_listAnimation.push_back(obj);

	//Add Monster

	for (int i = 0; i < m_DynamicMap.size(); i++)
	{
		for (int j = 0; j < m_DynamicMap[i].size(); j++)
		{
			switch (m_DynamicMap[i][j])
			{
			case 11: {
				printf("checkkkkkk\n");
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER1);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			case 22: {
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER2);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			case 33: {
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER3);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			case 44: {
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER4);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			}
		}
	}

	//Add gun
	m_gun = std::make_shared<Gun3>();
	m_player->SetGun(m_gun);

	m_KeyPress.Left = 0;
	m_KeyPress.Down = 0;
	m_KeyPress.Right = 0;
	m_KeyPress.Up = 0;


}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSPlay::LoadCSV(int level)
{
	std::ifstream file("Data/Map/dynamicmap"+std::to_string(s_pLevel)+".csv");
	if (!file.is_open()) {
		std::cerr << "Can not open CSV." << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ',')) {
			try {
				int cellValue = std::stoi(cell);
				row.push_back(cellValue);
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Cant convert data" << e.what() << std::endl;
			}
		}

		m_DynamicMap.push_back(row);
	}

	file.close();

	for (const auto& row : m_DynamicMap) {
		for (int cell : row) {
			std::cout << cell << "\t";
		}
		std::cout << std::endl;
	}
}

void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN)//&& e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			printf("MOVE LEFT\n");
			//m_KeyPress |= 1;
			m_KeyPress.Left = true;
			break;
		case SDLK_DOWN:
			printf("MOVE DOWN\n");
			//m_KeyPress |= 1 << 1;
			m_KeyPress.Down = true;
			break;
		case SDLK_RIGHT:
			printf("MOVE RIGHT\n");
			m_KeyPress.Right = true;
			//m_KeyPress |= 1 << 2;
			break;
		case SDLK_UP:
			printf("MOVE UP\n");
			m_KeyPress.Up = true;
			//m_KeyPress |= 1 << 3;
			break;
		default:
			break;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP)//&& e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress.Left = false;
			//m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress.Down = false;
			//m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress.Right = false;
			//m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress.Up = false;
			//m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMotionEvents(SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION) {
		aimMouse.x = e.motion.x;
		aimMouse.y = e.motion.y;
	}
}

void GSPlay::HandleMouseClickEvents(SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		printf("down\n");
		m_player->PullTrigger();
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		printf("up\n");
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	//switch (m_KeyPress)//Handle Key event
	//{
	//default:
	//	break;
	//}
	// Key State event

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	for (auto it : m_listMonster)
	{
		if (!it->IsHidden()) {
			it->Update(deltaTime);
		}
	}

	m_player->Update(deltaTime, m_KeyPress, aimMouse);
	
	HandleCollision(deltaTime);

}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);

	for (auto it : m_listMonster)
	{
		if (!it->IsHidden()) {
			it->Draw(renderer);
		}
	}

	m_player->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//m_projectile->Draw(renderer);
}


int GSPlay::s_pLevel;

void GSPlay::setLevel(int level)
{
	s_pLevel = level;
}

void GSPlay::HandleCollision(float deltaTime)
{
	m_player->HandleCollison(m_StaticMap, m_listMonster);
}
