#include "Projectile4.h"
#include <cmath>
#define ONE_RAD 180

Projectile4::Projectile4(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 400;
	m_frameCount = 5;
	m_frameTime = 0.5f;
}

Projectile4::~Projectile4()
{
}