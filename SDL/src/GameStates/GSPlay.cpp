#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("Actor1_2.tga");
	obj = std::make_shared<SpriteAnimation>(texture, 2, 9, 6, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(64, 64);
	obj->Set2DPosition(240, 400);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);


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
	for (auto it : m_listAnimation)
	{
		if (m_KeyPress.Left) {
			it->MoveLeft(deltaTime);
		}
		if (m_KeyPress.Down) {
			it->MoveDown(deltaTime);
		}
		if (m_KeyPress.Right) {
			it->MoveRight(deltaTime);
		}
		if (m_KeyPress.Up) {
			it->MoveTop(deltaTime);
		}

		it->Update(deltaTime);
	}

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}