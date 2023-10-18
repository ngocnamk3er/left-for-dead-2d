#pragma once
#include "Sprite2D.h"
#include "Projectile.h"
#include <list>

class Gun : public Sprite2D
{
public:

	//Initializes internal variable
	Gun();
	Gun(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	virtual void Shot();
	void UpdatePjectile(float deltatime);
	void Draw(SDL_Renderer* renderer);
	std::list<std::shared_ptr<Projectile>> GetListProjectile();
protected:
	std::shared_ptr<TextureManager> m_TextureProjectile;
	std::list<std::shared_ptr<Projectile>>	m_listProjectile;
	void DrawListProjectile(SDL_Renderer* renderer);
};

