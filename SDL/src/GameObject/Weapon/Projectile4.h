#pragma once
#include "Projectile.h"
class Projectile4 : public Projectile {
public:
	Projectile4(std::shared_ptr<TextureManager> texture, double angle);
	~Projectile4();
	void	Init() override;
	void	Update(float deltatime) override;
	void	UpdatePos(float deltatime);
	void	Draw(SDL_Renderer* renderer) override;
};
