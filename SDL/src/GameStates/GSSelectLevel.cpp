#include "GSSelectLevel.h"
#include "GSPlay.h"
#include <iostream>

GSSelectLevel::GSSelectLevel() : GameStateBase(StateType::STATE_SELECT_LEVEl),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSSelectLevel::~GSSelectLevel()
{
}



void GSSelectLevel::Init()
{
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

	for (int i = 1; i <= 3; i++)
	{
		printf("Make btn");
		texture = ResourceManagers::GetInstance()->GetTexture("GUI/Button.png");
		std::shared_ptr<MouseButton> btnSelectLevelI = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, std::to_string(i));
		//btnClose = std::make_shared<MouseButton>(texture);
		btnSelectLevelI->SetSize(128, 128);
		btnSelectLevelI->Set2DPosition(SCREEN_WIDTH / 2 - 320 + 256 * (i - 1), SCREEN_HEIDHT / 2 - 64);
		btnSelectLevelI->SetOnClick([i]() {//i is level
			GSPlay::setLevel(i);
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
		m_listButton.push_back(btnSelectLevelI);
	}

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
