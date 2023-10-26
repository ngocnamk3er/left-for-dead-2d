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
	DrawListHit(renderer);
	Sprite2D::Draw(renderer);
}

void Gun::AddHit(float x, float y)
{
	std::shared_ptr<TextureManager> texture = ResourceManagers::GetInstance()->GetTexture("hits/hit.png");
	std::shared_ptr<Hit> hit = std::make_shared<Hit>(texture, 1, 7, 1, 0.1f);
	hit->SetSize(32, 32);
	hit->Set2DPosition(x, y);
	m_listHit.push_back(hit);
}

std::list<std::shared_ptr<Projectile>> Gun::GetListProjectile()
{
	return m_listProjectile;
}

std::list<std::shared_ptr<Hit>> Gun::GetListHit()
{
	return m_listHit;
}

void Gun::UpdatePjectile(float deltatime)
{
	for each (auto projectile in m_listProjectile)
	{
		projectile->Update(deltatime);
	}
}

void Gun::UpdateHits(float deltatime)
{
	for each (auto hit in m_listHit)
	{
		hit->Update(deltatime);
	}
}

void Gun::DrawListProjectile(SDL_Renderer* renderer)
{
	for each (auto projectile in m_listProjectile)
	{
		projectile->Draw(renderer);
	}
}

void Gun::DrawListHit(SDL_Renderer* renderer)
{
	for each (auto hit in m_listHit)
	{
		hit->Draw(renderer);
	}
}

void Gun::Shot()
{
}
