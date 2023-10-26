#pragma once
#include "SpriteAnimation.h"
#include "GameManager/ResourceManagers.h"

class Hit : public SpriteAnimation {
public:
	Hit(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);
	~Hit();
	void	Init() override;
	void Update(float deltatime);
	void UpdateAnimation(float deltatime);
	virtual void Draw(SDL_Renderer* renderer);
protected:
	float m_speed;
};