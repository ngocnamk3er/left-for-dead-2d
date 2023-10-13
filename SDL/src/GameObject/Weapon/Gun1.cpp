#include "Gun1.h"
#include "GameManager/ResourceManagers.h"

Gun1::Gun1() {
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun1.png");
	m_flip = SDL_FLIP_NONE;
}

void Gun1::Shot()
{
	printf("gun 1 shot\n");
}
