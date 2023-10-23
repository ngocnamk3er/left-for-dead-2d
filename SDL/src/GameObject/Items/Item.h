#pragma once
#include "Sprite2D.h"

enum class ItemType
{
	GUN_1 = 11,
	GUN_2 = 22,
	GUN_3 = 33,
	GUN_4 = 44,
	IN_DOOR = 27,
	OUT_DOOR = 34
};

class Item : public Sprite2D
{
public:

	//Initializes internal variable
	Item();
	Item(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip, ItemType itemType);
	ItemType GetItemType();
	void Draw(SDL_Renderer* renderer);
private:
	ItemType m_pItemType;
};

