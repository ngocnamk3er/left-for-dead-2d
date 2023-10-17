#include "Projectile3.h"
#include <cmath>
#define ONE_RAD 180

Projectile3::Projectile3(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 200;
	m_frameCount = 4;
}

Projectile3::~Projectile3()
{
}