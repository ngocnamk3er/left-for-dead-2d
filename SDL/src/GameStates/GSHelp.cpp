#include "GSHelp.h"

GSHelp::GSHelp() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{})
{
}


GSHelp::~GSHelp()
{
}



void GSHelp::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);


	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);

	m_textColor = { 255, 255, 0 };
	m_textHelp = std::make_shared<Text>("Data/lazy.ttf", m_textColor);
	m_textHelp->SetSize(300, 50);
	m_textHelp->Set2DPosition((SCREEN_WIDTH - m_textHelp->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 300);
	m_textHelp->LoadFromRenderText("This is your guide");
	
}

void GSHelp::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSHelp::Pause()
{

}

void GSHelp::Resume()
{
	
}


void GSHelp::HandleEvents()
{
}

void GSHelp::HandleKeyEvents(SDL_Event& e)
{
}

void GSHelp::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSHelp::HandleMouseMoveEvents(int x, int y)
{
}

void GSHelp::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSHelp::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textHelp->Draw(renderer);
}
