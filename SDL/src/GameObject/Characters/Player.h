#pragma once
#include "GameObject/SpriteAnimation.h"
#include "Keyset.h"
#include "GameObject/Weapon/Gun.h"
#include "Weapon/AimMouse.h"
#include "Monster.h"
#include "Hitbox.h"
#include "Items/Item.h"
#include "GameObject/Weapon/Gun1.h"
#include "GameObject/Weapon/Gun2.h"
#include "GameObject/Weapon/Gun3.h"
#include "GameObject/Weapon/Gun4.h"
class Monster;
class Player : public SpriteAnimation {
public:
	Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Player();
	void		Init();
	void	Update(float deltatime, KeySet keyPress, AimMouse aimMouse, std::vector<std::vector<int>> StaticMap);
	void	UpdatePos(float deltatime);
	void	SetGun(std::shared_ptr<Gun> gun);
	void	Draw(SDL_Renderer* renderer) override;
	void PullTrigger();
	void HandleCollison(std::vector<std::vector<int>> StaticMap, std::list<std::shared_ptr<Monster>> listMonster, std::list<std::shared_ptr<Item>> listItems,float deltatime);
	void SetSpeed(KeySet keySet,std::vector<std::vector<int>> StaticMap, float deltatime);
	float GetHealth();
private:
	void SetGunAngle(AimMouse aimMouse);
	void DrawGun(SDL_Renderer* renderer);
	std::shared_ptr<Gun> m_gun;
	float m_pSpeedX = 0;
	float m_pSpeedY = 0;
	Hitbox m_pHitbox;
	void UpdateHitbox();
	float m_pHealth = 10;

};