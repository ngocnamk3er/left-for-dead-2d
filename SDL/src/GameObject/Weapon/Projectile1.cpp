#include "Projectile1.h"
#include <cmath>
#define ONE_RAD 180

Projectile1::Projectile1(std::shared_ptr<TextureManager> texture, double angle) : Projectile(texture, angle)
{
	m_speed = 200;
	m_frameCount = 6;
}

Projectile1::~Projectile1()
{
}

void Projectile1::Init()
{
}

void Projectile1::Update(float deltatime)
{
	//printf("Update projectile 1\n");
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
}

void Projectile1::UpdatePos(float deltatime)
{
	//printf("Update posssss projectile 1\n");
	m_position.x = m_position.x + m_speed * cos(m_angle / ONE_RAD * M_PI) * deltatime;
	m_position.y = m_position.y + m_speed * sin(m_angle / ONE_RAD * M_PI) * deltatime;
}

void Projectile1::Draw(SDL_Renderer* renderer)
{
	//printf("Draw projectile 1\n");
	Projectile::Draw(renderer);
}
