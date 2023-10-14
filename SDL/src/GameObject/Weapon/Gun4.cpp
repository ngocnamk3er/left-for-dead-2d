#include "Gun4.h"
#include "GameManager/ResourceManagers.h"
#include "Projectile4.h"
#include "Projectile.h"

#define ONE_RAD 180

Gun4::Gun4() {
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun4.png");
	m_TextureProjectile = ResourceManagers::GetInstance()->GetTexture("Shoot/projectile4.png");
	if (m_TextureProjectile == NULL) {
		printf("Could load projectile texture\n");
		return;
	}
	m_flip = SDL_FLIP_NONE;
}

void Gun4::Shot()
{
	std::shared_ptr<Projectile> newProjectile = std::make_shared<Projectile4>(m_TextureProjectile, m_angle);
	newProjectile->Set2DPosition(m_position.x + m_iWidth / 4, m_position.y);
	m_listProjectile.push_back(newProjectile);
}

void Gun4::Draw(SDL_Renderer* renderer)
{
	//printf("Draw 1\n");
	DrawListProjectile(renderer);
	Sprite2D::Draw(renderer);
}

void Gun4::UpdatePjectile(float deltatime)
{

	for each (auto projectile in m_listProjectile)
	{
		projectile->Update(deltatime);
	}
}

void Gun4::DrawListProjectile(SDL_Renderer* renderer)
{
	for each (std::shared_ptr<Projectile> projectile in m_listProjectile)
	{
		projectile->Draw(renderer);
	}
}