#include "GSOver.h"

GSOver::GSOver() : GameStateBase(StateType::STATE_OVER),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{})
{
}


GSOver::~GSOver()
{
	printf("Huy doi tuong GSHElp\n");
}



void GSOver::Init()
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

	m_textColor = { 255, 255, 255 };
	m_textHelp = std::make_shared<Text>("Data/Textures/GUI/m6x11.ttf", m_textColor);
	m_textHelp->SetSize(600, 50);
	m_textHelp->Set2DPosition((SCREEN_WIDTH - m_textHelp->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 150);
	m_textHelp->LoadFromRenderText("GAME OVER");

	m_textColor = { 255, 255, 255 };
	m_textHelp1 = std::make_shared<Text>("Data/Textures/GUI/m6x11.ttf", m_textColor);
	m_textHelp1->SetSize(600, 50);
	m_textHelp1->Set2DPosition((SCREEN_WIDTH - m_textHelp->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 50);
	m_textHelp1->LoadFromRenderText("CLICK ANY WHERE TO CONTINUE");
}

void GSOver::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSOver::Pause()
{

}

void GSOver::Resume()
{

}


void GSOver::HandleEvents()
{
}

void GSOver::HandleKeyEvents(SDL_Event& e)
{
}

void GSOver::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSOver::HandleMouseMotionEvents(SDL_Event& e)
{
}

void GSOver::HandleMouseClickEvents(SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
	}
}

void GSOver::HandleMouseMoveEvents(int x, int y)
{
}

void GSOver::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSOver::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	m_textHelp->Draw(renderer);
	m_textHelp1->Draw(renderer);
}
