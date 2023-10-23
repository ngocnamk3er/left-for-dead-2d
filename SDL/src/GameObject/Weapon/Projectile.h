#pragma once
#include "SpriteAnimation.h"
#include "GameManager/ResourceManagers.h"

class Projectile : public SpriteAnimation{
public:
	Projectile(std::shared_ptr<TextureManager> texture, double angle);
	Projectile(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);
	~Projectile();
	void	Init() override;
	void Update(float deltatime);
	void UpdatePos(float deltatime);
	virtual void Draw(SDL_Renderer* renderer);
	int GetWidth();
	int GetHeight();
	void SetSpeed(float speed);
protected:
	float m_speed;
};