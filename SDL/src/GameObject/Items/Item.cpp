#include "Item.h"
Item::Item() : Sprite2D()
{
	m_position.x = 0;
	m_position.y = 0;
}

Item::Item(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip, ItemType itemType)
	: Sprite2D(texture, flip)
{
	m_iHeight = 64;
	m_iWidth = 64;
	m_pItemType = itemType;
	m_pIsHidden = false;
}

ItemType Item::GetItemType()
{
	return m_pItemType;
}

void Item::Draw(SDL_Renderer* renderer)
{
	if (m_pIsHidden == false) {
		Sprite2D::Draw(renderer);
	}
}
