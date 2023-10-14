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
	virtual void UpdatePjectile(float deltatime);
	virtual void Draw(SDL_Renderer* renderer);
protected:
	std::shared_ptr<TextureManager> m_TextureProjectile;
	std::list<std::shared_ptr<Projectile>>	m_listProjectile;
	virtual void DrawListProjectile(SDL_Renderer* renderer);
};

