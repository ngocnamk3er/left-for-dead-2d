#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "GameObject/Sound.h"
class GSHelp :
	public GameStateBase
{
public:
	GSHelp();
	~GSHelp();

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

private:
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textHelp;
	std::shared_ptr<Text>					m_textHelp1;
	std::shared_ptr<Text>					m_textHelp2;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
};