#pragma once
#include <SDL.h>
#include "Sprite2D.h"
#include <functional>

class MouseButton : public Sprite2D
{
public:
	
	//Initializes internal variable
	MouseButton();
	MouseButton(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip, std::string text);

	//Handles mouse event
	bool HandleTouchEvent(SDL_Event* e);
	//void Draw(SDL_Renderer* renderer);
	//Show button sprite
	void Draw(SDL_Renderer * renderer) override;
	SDL_Point* GetButtonPosition();
	
	void	SetOnClick(std::function<void(void)>pBtClick);
private:
	std::function<void(void)>m_pBtClick;
	//Top left position
	SDL_Point* mPosition;
	//Currently used global sprite
	std::string m_text; 
	SDL_Color m_textColor;
	TTF_Font* m_pFont;
	
};

