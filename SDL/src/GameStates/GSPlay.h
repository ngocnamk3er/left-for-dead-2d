#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "GameObject/Characters/Player.h"
#include "GameObject/Characters/Monster.h"
#include "GameObject/Weapon/Gun.h"
#include "GameObject/Weapon/Gun1.h"
#include "GameObject/Weapon/Gun2.h"
#include "GameObject/Weapon/Gun3.h"
#include "GameObject/Weapon/Gun4.h"
#include "GameObject/Weapon/Projectile1.h"
#include "GameObject/Items/Item.h"

class Sprite2D;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init();
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	LoadCSV(int level);
	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMotionEvents(SDL_Event& e) override;
	void	HandleMouseClickEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	void	DrawHealthBar(SDL_Renderer* renderer);
	static void setLevel(int level);
	static int getLevel();
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
	std::shared_ptr<Projectile> m_projectile;
	std::shared_ptr<Gun> m_gun;
	std::list<std::shared_ptr<Item>> m_pListItems;
	std::shared_ptr<MouseButton> button;
	AimMouse aimMouse;
	float time = 0.0f;
	float m_Velocity = 10.0f;
	SDL_Surface* cursorIcon;
	SDL_Cursor* customCursor;
	std::vector<std::vector<int>> m_DynamicMap;
	std::vector<std::vector<int>> m_StaticMap;
	static int s_pLevel;


	void	HandleCollision(float deltaTime);
};