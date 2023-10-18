#include "Projectile1.h"
#include <cmath>
#define ONE_RAD 180

Projectile1::Projectile1(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 1000;
	m_frameCount = 6;
}

Projectile1::~Projectile1()
{
}
