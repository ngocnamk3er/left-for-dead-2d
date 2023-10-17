#pragma once
#include "Monster.h"


class Monster1 : public Monster {
public:
	Monster1(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Monster1();
};