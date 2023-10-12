#include "Projectile.h"
#define SPEEP_PROJECTILE 200
#include <cmath>

ProjectTile::ProjectTile(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime, double angle) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	m_angle = angle;
	speed = SPEEP_PROJECTILE;
	Init();
}

ProjectTile::~ProjectTile()
{
	printf("Huy doi tuong Projectile\n");
}

void ProjectTile::Init()
{
}

void ProjectTile::Update(float deltatime)
{
	m_position.x = m_position.x + SPEEP_PROJECTILE * cos(m_angle);
	m_position.y = m_position.y + SPEEP_PROJECTILE * sin(m_angle);
}
