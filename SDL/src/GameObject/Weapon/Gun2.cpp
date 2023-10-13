#include "Gun2.h"
#include "GameManager/ResourceManagers.h"

Gun2::Gun2() {
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun2.png");
	m_flip = SDL_FLIP_NONE;
}

void Gun2::Shot()
{
	printf("gun 2 shot\n");
}
