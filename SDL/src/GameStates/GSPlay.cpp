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
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/closeButton.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, " ");
	button->SetSize(64, 64);
	button->Set2DPosition(SCREEN_WIDTH - button->GetWidth() - 10, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// Add Player
	texture = ResourceManagers::GetInstance()->GetTexture("MainCharacter/3 Dude_Monster/Dude_Monster_Run_6.png");
	m_player = std::make_shared<Player>(texture, 1, 6, 1, 0.15f);
	m_player->SetSize(64, 64);
	m_player->Set2DPosition(240, 400);
	//Camera::GetInstance()->SetTarget(obj);
	//m_listAnimation.push_back(obj);

	//Add Monster
	for (int i = 0; i < 1; i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Zombies/BucketheadZombie/spritesheet_bucket.png");
		obj_monster = std::make_shared<Monster>(texture, 1, 15, 1, 0.15f);
		obj_monster->SetSize(83, 72);
		obj_monster->Set2DPosition(100 * i, 400);
		m_listMonster.push_back(obj_monster);
	}

	//Add gun
	m_gun = std::make_shared<Gun1>();
	//m_gun->SetFlip(SDL_FLIP_NONE);
	//Set gun for character
	m_player->SetGun(m_gun);

	m_KeyPress.Left = 0;
	m_KeyPress.Down = 0;
	m_KeyPress.Right = 0;
	m_KeyPress.Up = 0;

	cursorIcon = IMG_Load("Data/Textures/GUI/target.svg");
	customCursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
	SDL_FreeSurface(cursorIcon);
	SDL_SetCursor(customCursor);
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
		it->Update(deltaTime);
	}

	m_player->Update(deltaTime, m_KeyPress, aimMouse);

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);

	for (auto it : m_listMonster)
	{
		it->Draw(renderer);
	}

	m_player->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
}
