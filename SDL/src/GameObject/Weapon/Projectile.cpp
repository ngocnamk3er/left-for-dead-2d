#include "Projectile.h"
#include <cmath>

#define ONE_RAD 180

Projectile::Projectile(std::shared_ptr<TextureManager> texture, double angle) : SpriteAnimation(texture)
{
	m_pTexture = texture;
	m_angle = angle;
	m_speed = 200;
	m_spriteRow = 1;
	m_numAction = 1;
	m_frameTime = 0.1f;
	m_iHeight = 24;
	m_iWidth = 32;
}


Projectile::Projectile(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) 
	: SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{

	Init();
}

Projectile::~Projectile()
{
}

void Projectile::Init()
{
}

void Projectile::Update(float deltatime)
{
	if (m_pIsHidden==false) {
		printf("update projectile\n");
		UpdatePos(deltatime);
		UpdateAnimation(deltatime);
	}
}

void Projectile::UpdatePos(float deltatime)
{
	m_position.x = m_position.x + m_speed * cos(m_angle / ONE_RAD * M_PI) * deltatime;
	m_position.y = m_position.y + m_speed * sin(m_angle / ONE_RAD * M_PI) * deltatime;
}
void Projectile::Draw(SDL_Renderer* renderer)
{
	if (!m_pIsHidden) {
		SpriteAnimation::Draw(renderer);
	}
}

int Projectile::GetWidth()
{
	return m_iWidth;
}

int Projectile::GetHeight()
{
	return m_iHeight;
}

void Projectile::SetSpeed(float speed)
{
	m_speed = speed;
}
