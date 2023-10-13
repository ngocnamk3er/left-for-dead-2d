#pragma once
#include "GameObject/SpriteAnimation.h"
#include "Keyset.h"
#include "GameObject/Weapon/Gun.h"
#include "Weapon/AimMouse.h"

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
private:
	void UpdateGunPos(AimMouse aimMouse);
	void DrawGun(SDL_Renderer* renderer);
	std::shared_ptr<Gun> m_gun;
};