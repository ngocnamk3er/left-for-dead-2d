#pragma once
#include "Projectile.h"
class Projectile1 : public Projectile {
public:
	Projectile1(std::shared_ptr<TextureManager> texture, double angle);
	~Projectile1();
	void	Init() override;
	void	Update(float deltatime) override;
	void	UpdatePos(float deltatime);
	void	Draw(SDL_Renderer* renderer) override;
};
