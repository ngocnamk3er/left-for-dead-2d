#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "GameObject/Sound.h"
class GSSelectLevel :
	public GameStateBase
{
public:
	GSSelectLevel();
	~GSSelectLevel();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMotionEvents(SDL_Event& e) override;
	void	HandleMouseClickEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	void static	LoadCSV();
	void static SaveCSV();
	void static InCreHighestLevel();
	int static GetHighestLevel();
private:
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
	SDL_Surface* cursorIcon;
	SDL_Cursor* customCursor;
	static int m_pHighestLevel;
};