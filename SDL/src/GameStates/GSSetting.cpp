#include "GSSetting.h"
#include "GSPlay.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Setting.h"

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

	//Setting game


	//music btn
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/menuButton.png");
	std::shared_ptr<MouseButton> m_pButtonnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, "OFF MUSIC");
	m_pButtonnMusic->SetSize(200, 50);
	m_pButtonnMusic->Set2DPosition((SCREEN_WIDTH - m_pButtonnMusic->GetWidth()) / 2, (SCREEN_HEIDHT - m_pButtonnMusic->GetHeight()) / 2 + 100);
	m_pButtonnMusic->SetOnClick([m_pButtonnMusic]() {
		if (Setting::music == true) {
			Setting::music = false;
			m_pButtonnMusic->SetText("ON MUSIC");
		}
		else {
			Setting::music = true;
			m_pButtonnMusic->SetText("OFF MUSIC");
		}
		});
	m_listButton.push_back(m_pButtonnMusic);

	//SFX button
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/menuButton.png");
	std::shared_ptr<MouseButton> sfxMusicButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, "OFF SFX");
	sfxMusicButton->SetSize(200, 50);
	sfxMusicButton->Set2DPosition((SCREEN_WIDTH - m_pButtonnMusic->GetWidth()) / 2, (SCREEN_HEIDHT - sfxMusicButton->GetHeight()) / 2 );
	sfxMusicButton->SetOnClick([sfxMusicButton]() {
		if (Setting::sfx == true) {
			Setting::sfx = false;
			sfxMusicButton->SetText("ON SFX");
		}
		else {
			Setting::sfx = true;
			sfxMusicButton->SetText("OFF SFX");
		}
		});
	m_listButton.push_back(sfxMusicButton);

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


