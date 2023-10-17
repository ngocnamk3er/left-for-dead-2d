#include "Projectile2.h"
#include <cmath>
#define ONE_RAD 180

Projectile2::Projectile2(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 200;
	m_frameCount = 6;
}

Projectile2::~Projectile2()
{
}

