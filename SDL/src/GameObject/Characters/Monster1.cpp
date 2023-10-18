#include "Monster1.h"

Monster1::Monster1(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : Monster(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_speed = 100;
}

Monster1::~Monster1()
{
	printf("huy doi truong monster1\n");
}
