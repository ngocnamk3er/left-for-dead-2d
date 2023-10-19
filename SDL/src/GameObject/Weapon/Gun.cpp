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
	DrawListProjectile(renderer);
	Sprite2D::Draw(renderer);
}

std::list<std::shared_ptr<Projectile>> Gun::GetListProjectile()
{
	return m_listProjectile;
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
		if (!projectile->IsHidden()) {
			
			projectile->Draw(renderer);
		}
	}
}

void Gun::Shot()
{
}
