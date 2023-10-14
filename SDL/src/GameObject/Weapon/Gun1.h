#pragma once
#include "Gun.h"
class Gun1 : public Gun {
public:
	Gun1();
	void Shot() override;
	void UpdatePjectile(float deltatime) override;
	void Draw(SDL_Renderer* renderer) override;
protected:
	void DrawListProjectile(SDL_Renderer* renderer) override;
};