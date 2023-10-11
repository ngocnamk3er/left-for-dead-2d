#pragma once
#include "Sprite2D.h"

class Gun : public Sprite2D
{
public:

	//Initializes internal variable
	Gun();
	Gun(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
};

