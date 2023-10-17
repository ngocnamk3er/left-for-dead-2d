#pragma once
#include "Projectile.h"
class Projectile4 : public Projectile {
public:
	Projectile4(std::shared_ptr<TextureManager> texture, double angle);
	~Projectile4();
};
