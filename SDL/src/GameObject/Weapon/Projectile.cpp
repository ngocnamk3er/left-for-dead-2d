#include "Projectile.h"
#include <cmath>

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
	printf("%f\n", m_angle);
}


Projectile::Projectile(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) 
	: SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{

	Init();
}

Projectile::~Projectile()
{
	//printf("Huy doi tuong Projectile\n");
}

void Projectile::Init()
{
}

void Projectile::Update(float deltatime)
{
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
}

void Projectile::UpdatePos(float deltatime)
{

}
void Projectile::Draw(SDL_Renderer* renderer)
{
	SpriteAnimation::Draw(renderer);
}
