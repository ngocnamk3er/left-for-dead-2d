#include "Monster.h"

Monster::Monster(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}
Monster::~Monster()
{

}

void Monster::Init()
{

}

void	Monster::Update(float deltatime) {
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
};
void	Monster::UpdatePos(float deltatime) {
	
};