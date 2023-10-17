#pragma once
#include "Monster.h"


class Monster2 : public Monster {
public:
	Monster2(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Monster2();
};