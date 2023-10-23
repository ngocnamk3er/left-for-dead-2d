#include "GSSetting.h"
#include "GSPlay.h"
#include <iostream>
#include <fstream>
#include <string>

GSSetting::GSSetting() : GameStateBase(StateType::STATE_SELECT_LEVEl),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSSetting::~GSSetting()
{
	printf("Huy doi truong GSSetting\n");
}


void GSSetting::Init()
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
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
	SDL_SetCursor(customCursor);
}


void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(SDL_Event& e)
{
}

void GSSetting::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSSetting::HandleMouseMotionEvents(SDL_Event& e)
{
}

void GSSetting::HandleMouseClickEvents(SDL_Event& e)
{
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

}


