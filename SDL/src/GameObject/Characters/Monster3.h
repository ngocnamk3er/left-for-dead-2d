#pragma once
#include "Monster.h"


class Monster3 : public Monster {
public:
	Monster3(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Monster3();
};