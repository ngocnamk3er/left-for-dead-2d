#include "Projectile4.h"
#include <cmath>
#define ONE_RAD 180

Projectile4::Projectile4(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 500;
	m_frameCount = 5;
	m_frameTime = 0.5f;
}

Projectile4::~Projectile4()
{
}

void Projectile4::Init()
{
}

void Projectile4::Update(float deltatime)
{
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
}

void Projectile4::UpdatePos(float deltatime)
{
	m_position.x = m_position.x + m_speed * cos(m_angle / ONE_RAD * M_PI) * deltatime;
	m_position.y = m_position.y + m_speed * sin(m_angle / ONE_RAD * M_PI) * deltatime;
}

void Projectile4::Draw(SDL_Renderer* renderer)
{
	//printf("Draw projectile 2\n");
	Projectile::Draw(renderer);
}
