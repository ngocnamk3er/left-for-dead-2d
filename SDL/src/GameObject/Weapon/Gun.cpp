#include "Gun.h"
Gun::Gun() : Sprite2D()
{
	m_position.x = 0;
	m_position.y = 0;
}

Gun::Gun(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	: Sprite2D(texture, flip)
{
}

void Gun::Draw(SDL_Renderer* renderer)
{
	Sprite2D::Draw(renderer);
	DrawListProjectile(renderer);
}

void Gun::UpdatePjectile(float deltatime)
{
	for each (auto projectile in m_listProjectile)
	{
		projectile->Update(deltatime);
	}
}

void Gun::DrawListProjectile(SDL_Renderer* renderer)
{
	for each (auto projectile in m_listProjectile)
	{
		projectile->Draw(renderer);
	}
}

void Gun::Shot()
{
	//printf("parent gun shot\n");
}

//void Gun::Shot()
//{
//	printf("I am shooting\n");
//}
