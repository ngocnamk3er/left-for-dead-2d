#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "GameObject/Characters/Player.h"
#include "GameObject/Characters/Monster.h"
#include "GameObject/Weapon/Gun.h"

class Sprite2D;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	KeySet m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Monster>>	m_listMonster;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<Monster> obj_monster;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Gun> m_gun;
	std::shared_ptr<MouseButton> button;
	
	float time = 0.0f;
	float m_Velocity = 10.0f;
};
