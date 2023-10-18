#include "Monster2.h"

Monster2::Monster2(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : Monster(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_speed = 100;
}

Monster2::~Monster2()
{
	printf("huy doi truong monster2\n");
}
