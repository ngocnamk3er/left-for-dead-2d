#include "Projectile2.h"
#include <cmath>
#define ONE_RAD 180

Projectile2::Projectile2(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 300;
	m_frameCount = 6;
}

Projectile2::~Projectile2()
{
}

void Projectile2::Init()
{
}

void Projectile2::Update(float deltatime)
{
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
}

void Projectile2::UpdatePos(float deltatime)
{
	m_position.x = m_position.x + m_speed * cos(m_angle / ONE_RAD * M_PI) * deltatime;
	m_position.y = m_position.y + m_speed * sin(m_angle / ONE_RAD * M_PI) * deltatime;
}

void Projectile2::Draw(SDL_Renderer* renderer)
{
	//printf("Draw projectile 2\n");
	Projectile::Draw(renderer);
}
