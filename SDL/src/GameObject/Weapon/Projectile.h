#pragma once
#include "SpriteAnimation.h"

class ProjectTile : public SpriteAnimation{
public:
	ProjectTile(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime, double angle);
	~ProjectTile();
	void	Init() override;
	void	Update(float deltatime);
	void	UpdatePos(float deltatime);
private:
	float speed;
};