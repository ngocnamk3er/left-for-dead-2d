#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "GameStates/GSSelectLevel.h"
#include "KeyState.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


GSPlay::GSPlay() : GameStateBase(StateType::STATE_PLAY)
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
	auto texture = ResourceManagers::GetInstance()->GetTexture("Map/map" + std::to_string(s_pLevel) + ".jpg");

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
	m_player->Set2DPosition(0, 64);
	//Camera::GetInstance()->SetTarget(obj);
	//m_listAnimation.push_back(obj);

	//Add Monster

	for (int i = 0; i < m_DynamicMap.size(); i++)
	{
		for (int j = 0; j < m_DynamicMap[i].size(); j++)
		{
			switch (m_DynamicMap[i][j])
			{
			case (int)MonsterType::MONSTER1: {
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER1);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			case (int)MonsterType::MONSTER2: {
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER2);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			case (int)MonsterType::MONSTER3: {
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER3);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			case (int)MonsterType::MONSTER4: {
				obj_monster = Monster::CreateMonster(MonsterType::MONSTER4);
				obj_monster->Set2DPosition(j * 64, i * 64);
				m_listMonster.push_back(obj_monster);
				break;
			}
			case (int)ItemType::GUN_1: {
				texture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun1.png");
				std::shared_ptr<Item> item = std::make_shared<Item>(texture, SDL_FLIP_NONE, ItemType::GUN_1);
				item->Set2DPosition(j * 64 + 16, i * 64 + 32);
				item->SetSize(32, 12);
				m_pListItems.push_back(item);
				break;
			}
			case (int)ItemType::GUN_2: {
				texture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun2.png");
				std::shared_ptr<Item> item = std::make_shared<Item>(texture, SDL_FLIP_NONE, ItemType::GUN_2);
				item->Set2DPosition(j * 64 + 16, i * 64 + 32);
				item->SetSize(32, 12);
				m_pListItems.push_back(item);
				break;
			}
			case (int)ItemType::GUN_3: {
				texture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun3.png");
				std::shared_ptr<Item> item = std::make_shared<Item>(texture, SDL_FLIP_NONE, ItemType::GUN_3);
				item->Set2DPosition(j * 64 + 16, i * 64 + 32);
				item->SetSize(32, 12);
				m_pListItems.push_back(item);
				break;
			}
			case (int)ItemType::GUN_4: {
				texture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun4.png");
				std::shared_ptr<Item> item = std::make_shared<Item>(texture, SDL_FLIP_NONE, ItemType::GUN_4);
				item->Set2DPosition(j * 64 + 16, i * 64 + 32);
				item->SetSize(32, 12);
				m_pListItems.push_back(item);
				break;
			}
			case (int)ItemType::IN_DOOR: {
				texture = ResourceManagers::GetInstance()->GetTexture("GUI/indoor.png");
				m_pIndoor = std::make_shared<Item>(texture, SDL_FLIP_NONE, ItemType::IN_DOOR);
				m_pIndoor->Set2DPosition(j * 64, i * 64);
				m_pIndoor->SetSize(64, 64);
				break;
			}
			case (int)ItemType::OUT_DOOR: {
				texture = ResourceManagers::GetInstance()->GetTexture("GUI/outdoor.png");
				m_pOutdoor = std::make_shared<Item>(texture, SDL_FLIP_NONE, ItemType::OUT_DOOR);
				m_pOutdoor->Set2DPosition(j * 64, i * 64);
				m_pOutdoor->SetSize(64, 64);
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

	//make dynamic map
	std::ifstream file("Data/Map/dynamicmap" + std::to_string(s_pLevel) + ".csv");
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


	//make static map
	std::ifstream fileStaticmap("Data/Map/staticmap" + std::to_string(s_pLevel) + ".csv");
	if (!fileStaticmap.is_open()) {
		std::cerr << "Can not open CSV." << std::endl;
		return;
	}

	std::string lineStaticmap;
	while (std::getline(fileStaticmap, lineStaticmap)) {
		std::vector<int> row;
		std::stringstream ss(lineStaticmap);
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

		m_StaticMap.push_back(row);
	}

	fileStaticmap.close();

	for (int i = 0; i < m_StaticMap.size(); i++)
	{
		for (int j = 0; j < m_StaticMap[i].size(); j++) {
			printf("%d ", m_StaticMap[i][j]);
		}
		printf("\n");
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
			m_KeyPress.Left = true;
			break;
		case SDLK_DOWN:
			m_KeyPress.Down = true;
			break;
		case SDLK_RIGHT:
			m_KeyPress.Right = true;
			break;
		case SDLK_UP:
			m_KeyPress.Up = true;
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
		m_player->PullTrigger();
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
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
	//HandleCollision(deltaTime);

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	for (auto it : m_listMonster)
	{
		if (!it->IsHidden()) {
			it->Update(deltaTime, m_player->Get2DPosition(), m_StaticMap);
		}
	}

	m_player->Update(deltaTime, m_KeyPress, aimMouse, m_StaticMap);


	int count = 0;
	for each (auto monster in m_listMonster)
	{
		if (monster->IsHidden()) {
			count++;
		}
	}
	if (m_pIsWin == true) {
		if (GSPlay::getLevel() == 6) {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		}
		else {
			GSPlay::setLevel(GSPlay::getLevel() + 1);
			if (GSPlay::getLevel() > GSSelectLevel::GetHighestLevel()) {
				GSSelectLevel::InCreHighestLevel();
			}
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		}
	}
	HandleCollision(deltaTime);
	if (m_player->GetHealth() <= 0) {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
	}

}

void GSPlay::Draw(SDL_Renderer* renderer)
{

	m_background->Draw(renderer);

	m_pIndoor->Draw(renderer);

	m_pOutdoor->Draw(renderer);


	for (std::shared_ptr<Monster> it : m_listMonster)
	{
		if (!it->IsHidden()) {
			it->Draw(renderer);
		}
	}

	m_player->Draw(renderer);
	
	for (auto it : m_pListItems)
	{
		it->Draw(renderer);
	}

	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//Draw thanh mau
	//DrawHealthBar(renderer);
}


int GSPlay::s_pLevel;

void GSPlay::setLevel(int level)
{
	s_pLevel = level;
}

int GSPlay::getLevel()
{
	return s_pLevel;
}

void GSPlay::HandleCollision(float deltaTime)
{
	m_player->HandleCollison(m_StaticMap, m_listMonster,m_pListItems, deltaTime);

	if (sqrt((pow(abs(m_player->Get2DPosition().x - m_pOutdoor->Get2DPosition().x), 2) + pow(abs(m_player->Get2DPosition().y - m_pOutdoor->Get2DPosition().y), 2))) <= 48) {
		m_pIsWin = true;
	}

}
