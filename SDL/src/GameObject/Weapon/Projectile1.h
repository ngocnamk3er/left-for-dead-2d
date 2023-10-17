#pragma once
#include "Projectile.h"
class Projectile1 : public Projectile {
public:
	Projectile1(std::shared_ptr<TextureManager> texture, double angle);
	~Projectile1();
};
