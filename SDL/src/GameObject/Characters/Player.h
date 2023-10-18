#pragma once
#include "GameObject/SpriteAnimation.h"
#include "Keyset.h"
#include "GameObject/Weapon/Gun.h"
#include "Weapon/AimMouse.h"
#include "Monster.h"

class Player : public SpriteAnimation {
public:
	Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Player();
	void		Init();
	void	Update(float deltatime, KeySet keyPress, AimMouse aimMouse);
	void	UpdatePos(float deltatime, KeySet keyPress);
	void	SetGun(std::shared_ptr<Gun> gun);
	void	Draw(SDL_Renderer* renderer) override;
	void PullTrigger();
	void HandleCollison(std::vector<std::vector<int>> StaticMap, std::list<std::shared_ptr<Monster>>	listMonster);
private:
	void SetGunAngle(AimMouse aimMouse);
	void DrawGun(SDL_Renderer* renderer);
	std::shared_ptr<Gun> m_gun;

};