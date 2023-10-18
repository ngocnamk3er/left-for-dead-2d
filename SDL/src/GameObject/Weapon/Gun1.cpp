#include "Gun1.h"
#include "GameManager/ResourceManagers.h"
#include "Projectile1.h"
#include "Projectile.h"

#define ONE_RAD 180

Gun1::Gun1() {
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("Gun/Gun1.png");
	m_TextureProjectile = ResourceManagers::GetInstance()->GetTexture("Shoot/projectile1.png");
	if (m_TextureProjectile == NULL) {
		printf("Could load projectile texture\n");
		return;
	}
	m_flip = SDL_FLIP_NONE;
}

void Gun1::Shot()
{
	std::shared_ptr<Projectile> newProjectile = std::make_shared<Projectile1>(m_TextureProjectile, m_angle);
	newProjectile->Set2DPosition(m_position.x + m_iWidth / 4, m_position.y);
	m_listProjectile.push_back(newProjectile);
}
