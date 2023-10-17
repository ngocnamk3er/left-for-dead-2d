#pragma once
#include "Projectile.h"
class Projectile2 : public Projectile {
public:
	Projectile2(std::shared_ptr<TextureManager> texture, double angle);
	~Projectile2();
};
