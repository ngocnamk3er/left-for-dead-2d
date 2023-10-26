#pragma once
#include "Sprite2D.h"
#include "Projectile.h"
#include <list>
#include "Hit.h"

class Gun : public Sprite2D
{
public:

	//Initializes internal variable
	Gun();
	Gun(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	virtual void Shot();
	void UpdatePjectile(float deltatime);
	void UpdateHits(float deltatime);
	void Draw(SDL_Renderer* renderer);
	void AddHit(float x, float y);
	void AddHit();
	std::list<std::shared_ptr<Projectile>> GetListProjectile();
	std::list<std::shared_ptr<Hit>> GetListHit();
protected:
	std::shared_ptr<TextureManager> m_TextureProjectile;
	std::list<std::shared_ptr<Projectile>>	m_listProjectile;
	std::list<std::shared_ptr<Hit>>	m_listHit;
	void DrawListProjectile(SDL_Renderer* renderer);
	void DrawListHit(SDL_Renderer* renderer);
};

