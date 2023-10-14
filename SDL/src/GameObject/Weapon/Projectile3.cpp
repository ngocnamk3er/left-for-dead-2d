#include "Projectile3.h"
#include <cmath>
#define ONE_RAD 180

Projectile3::Projectile3(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 400;
	m_frameCount = 4;
}

Projectile3::~Projectile3()
{
}

void Projectile3::Init()
{
}

void Projectile3::Update(float deltatime)
{
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
}

void Projectile3::UpdatePos(float deltatime)
{
	m_position.x = m_position.x + m_speed * cos(m_angle / ONE_RAD * M_PI) * deltatime;
	m_position.y = m_position.y + m_speed * sin(m_angle / ONE_RAD * M_PI) * deltatime;
}

void Projectile3::Draw(SDL_Renderer* renderer)
{
	Projectile::Draw(renderer);
}
