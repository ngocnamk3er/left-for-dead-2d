#include "Hit.h"
#include <cmath>


Hit::Hit(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
	: SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{

	Init();
}

Hit::~Hit()
{
}

void Hit::Init()
{
	m_pIsHidden = false;
}

void Hit::Update(float deltatime)
{
	if (m_pIsHidden == false) {
		UpdateAnimation(deltatime);
	}
}

void Hit::UpdateAnimation(float deltatime) {
	m_currentTicks += deltatime;
	if (m_currentTicks >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
			m_pIsHidden = true;
		}
		m_currentTicks -= m_frameTime;
	}
}

void Hit::Draw(SDL_Renderer* renderer)
{
	if(!m_pIsHidden) {
		SpriteAnimation::Draw(renderer);
	}
}

