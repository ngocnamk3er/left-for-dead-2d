#pragma once
#include "Monster.h"


class Monster4 : public Monster {
public:
	Monster4(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Monster4();
};