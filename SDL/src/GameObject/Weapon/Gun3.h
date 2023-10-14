#pragma once
#include "Gun.h"
class Gun3 : public Gun {
public:
	Gun3();
	void Shot() override;
	void UpdatePjectile(float deltatime) override;
	void Draw(SDL_Renderer* renderer) override;
protected:
	void DrawListProjectile(SDL_Renderer* renderer) override;
};