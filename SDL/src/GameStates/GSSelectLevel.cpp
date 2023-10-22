#include "GSSelectLevel.h"
#include "GSPlay.h"
#include <iostream>
#include <fstream>
#include <string>

GSSelectLevel::GSSelectLevel() : GameStateBase(StateType::STATE_SELECT_LEVEl),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSSelectLevel::~GSSelectLevel()
{
	printf("Huy doi truong GSSelectLevel\n");
}

int GSSelectLevel::m_pCurrentLevel;

void GSSelectLevel::Init()
{
	//LoadCSV();
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("GUI/menuBG.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/closeButton.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, " ");
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(64, 64);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth() - 10, 10);
	btnClose->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);

	//set Cursor icon
	cursorIcon = IMG_Load("Data/Textures/GUI/cursor_select.png");
	customCursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
	SDL_SetCursor(customCursor);

	for (int i = 1; i <= 2; i++)
	{
		for (int j = 1; j <= 3; j++) 
		{
			if ((i - 1) * 3 + j <= m_pCurrentLevel) {
				texture = ResourceManagers::GetInstance()->GetTexture("GUI/Button.png");
				std::shared_ptr<MouseButton> btnSelectLevelI = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, std::to_string((i - 1)*3+j))	;
				//btnClose = std::make_shared<MouseButton>(texture);
				btnSelectLevelI->SetSize(128, 128);
				btnSelectLevelI->Set2DPosition(SCREEN_WIDTH / 2 - 320 + 256 * (j - 1), SCREEN_HEIDHT / 2 - 192 + (i-1) * 256);
				btnSelectLevelI->SetOnClick([i, j]() {//i is level
					GSPlay::setLevel((i - 1) * 3 + j);
					GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
					});
				m_listButton.push_back(btnSelectLevelI);
			}
		}
	}

}

void GSSelectLevel::LoadCSV()
{
	std::string file_path = "Data/data.txt";
	std::ifstream file(file_path);

	if (file.is_open()) {
		std::string line;
		if (std::getline(file, line)) {
			try {
				m_pCurrentLevel = std::stoi(line);
				std::cout << "Curent Level: " << m_pCurrentLevel << std::endl;
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Cant convert to int: " << std::endl;
			}
		}
		else {
			std::cerr << "Have no data in file: " << std::endl;
		}
		file.close();
	}
	else {
		std::cerr << "Cant open file: " << std::endl;
	}

	return;
}

void GSSelectLevel::SaveCSV()
{
	int number_to_save = m_pCurrentLevel;
	std::string file_path = "Data/data.txt"; 

	std::ofstream file(file_path, std::ios::out | std::ios::trunc);

	if (file.is_open()) {
		file << number_to_save << std::endl;
		file.close();
		std::cout << "Saved" << std::endl;
	}
	else {
		std::cerr << "Cant open" << std::endl;
	}

	return;
}

void GSSelectLevel::InCreCurrentLevel()
{
	m_pCurrentLevel++;
}

int GSSelectLevel::GetLevel()
{
	return m_pCurrentLevel;
}

void GSSelectLevel::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSSelectLevel::Pause()
{


}

void GSSelectLevel::Resume()
{
	SDL_SetCursor(customCursor);
	for (int i = 1; i <= 2; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			if ((i - 1) * 3 + j <= m_pCurrentLevel) {
				std::shared_ptr<TextureManager> texture = ResourceManagers::GetInstance()->GetTexture("GUI/Button.png");
				std::shared_ptr<MouseButton> btnSelectLevelI = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, std::to_string((i - 1) * 3 + j));
				//btnClose = std::make_shared<MouseButton>(texture);
				btnSelectLevelI->SetSize(128, 128);
				btnSelectLevelI->Set2DPosition(SCREEN_WIDTH / 2 - 320 + 256 * (j - 1), SCREEN_HEIDHT / 2 - 192 + (i - 1) * 256);
				btnSelectLevelI->SetOnClick([i, j]() {//i is level
					GSPlay::setLevel((i - 1) * 3 + j);
					GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
					});
				m_listButton.push_back(btnSelectLevelI);
			}
		}
	}
}


void GSSelectLevel::HandleEvents()
{
}

void GSSelectLevel::HandleKeyEvents(SDL_Event& e)
{
}

void GSSelectLevel::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSSelectLevel::HandleMouseMotionEvents(SDL_Event& e)
{
}

void GSSelectLevel::HandleMouseClickEvents(SDL_Event& e)
{
}

void GSSelectLevel::HandleMouseMoveEvents(int x, int y)
{
}

void GSSelectLevel::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSelectLevel::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

}


