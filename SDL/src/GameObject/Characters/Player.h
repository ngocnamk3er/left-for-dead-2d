#pragma once
#include "GameObject/SpriteAnimation.h"
#include "Keyset.h"


class Player : public SpriteAnimation {
public:
	Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Player();
	void		Init() override;
	void	Update(float deltatime, KeySet keyPress);
	void	UpdatePos(float deltatime, KeySet keyPress);
};