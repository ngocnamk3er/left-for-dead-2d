#include "GSMenu.h"
#include "Setting.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
	printf("Huy doi tuong GS Menu\n");
}



void GSMenu::Init()
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
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);


	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/menuButton.png");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, "Play");

	btnPlay->SetSize(200, 50);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([]() {
		printf("check");
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SELECT_LEVEl);
		});
	m_listButton.push_back(btnPlay);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/menuButton.png");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, "Settings");
	btnOption->SetSize(200, 50);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2 + 100);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SETTING);
		});
	m_listButton.push_back(btnOption);

	//Help game
	texture = ResourceManagers::GetInstance()->GetTexture("GUI/menuButton.png");
	btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE, "Help");
	btnCredit->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2 + 200);
	btnCredit->SetSize(200, 50);
	btnCredit->SetOnClick([]() {
		printf("check");
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnCredit);

	// game title
	///Set Font
	m_textColor = { 255, 255, 255 };
	m_textGameName = std::make_shared<Text>("Data/Textures/GUI/m6x11.ttf", m_textColor);
	m_textGameName->SetSize(300, 50);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 150);
	m_textGameName->LoadFromRenderText("LEFT 4 DEAD 2D");

	if (Setting::music == true) {
		m_Sound = std::make_shared<Sound>();
		m_Sound->LoadSound("Data/Sounds/MUSIC/play_music.mp3");
		m_Sound->PlaySound();
	}


	//cursorIcon = IMG_Load("Data/Textures/GUI/cursorImage.png");
	//customCursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
	//SDL_FreeSurface(cursorIcon);
	//SDL_SetCursor(customCursor);

	cursorIcon = IMG_Load("Data/Textures/GUI/cursor_select.png");
	customCursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
	SDL_FreeSurface(cursorIcon);
	SDL_SetCursor(customCursor);

}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	if (Setting::music == true) {
		m_Sound->StopSound();
	}
}

void GSMenu::Resume()
{
	if (Setting::music == true) {
		m_Sound->PlaySound();
		SDL_SetCursor(customCursor);
	}
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMotionEvents(SDL_Event& e)
{
}

void GSMenu::HandleMouseClickEvents(SDL_Event& e)
{
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	m_textGameName->Draw(renderer);
}
