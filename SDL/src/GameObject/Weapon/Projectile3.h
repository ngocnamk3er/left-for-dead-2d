#pragma once
#include "Projectile.h"
class Projectile3 : public Projectile {
public:
	Projectile3(std::shared_ptr<TextureManager> texture, double angle);
	~Projectile3();
	void	Init() override;
	void	Update(float deltatime) override;
	void	UpdatePos(float deltatime);
	void	Draw(SDL_Renderer* renderer) override;
};
