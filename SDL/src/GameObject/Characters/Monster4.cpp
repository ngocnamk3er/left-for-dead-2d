#include "Monster4.h"

Monster4::Monster4(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : Monster(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_speed = 100;
}

Monster4::~Monster4()
{
	printf("huy doi truong monster4\n");
}
