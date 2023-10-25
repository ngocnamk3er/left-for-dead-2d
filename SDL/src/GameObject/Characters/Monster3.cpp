#include "Monster3.h"

Monster3::Monster3(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : Monster(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_pMaxSpeed = 250;
}

Monster3::~Monster3()
{
	printf("huy doi truong monster3\n");
}
