#include "MouseButton.h"
#include "Game.h"
#include "TextureManager.h"
#include <SDL_ttf.h>

MouseButton::MouseButton() : Sprite2D(), m_pBtClick(nullptr), m_pFont(nullptr)
{
    m_position.x = 0;
    m_position.y = 0;
}

MouseButton::MouseButton(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip, std::string text)
    : Sprite2D(texture, flip), m_pBtClick(nullptr), m_pFont(nullptr)
{
    m_textColor = { 255, 255, 255};
    m_pFont = TTF_OpenFont("Data/Textures/GUI/m6x11.ttf", 28); 
    m_text = text;
    if (m_pFont == nullptr)
    {
    }
}

bool MouseButton::HandleTouchEvent(SDL_Event* e)
{
    //If mouse event happened (clicked/released...
    if (e->type == SDL_MOUSEBUTTONUP)//|| e->type == SDL_MOUSEBUTTONDOWN) e->type == SDL_MOUSEMOTION || 
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        // Check if mouse is in button
        bool inside = true;
        //Mouse is left/right above/below of the button
        if (x < m_position.x || x > m_position.x + m_iWidth || y < m_position.y || y > m_position.y + m_iHeight)
        {
            inside = false;
        }
        // Mouse is outside button
        if (inside)
        {
            // Only perform click action when the same button was pressed down and released
            m_pBtClick();
        }
        //if (e->button.button == SDL_BUTTON_LEFT)
        //{
            ///  perform left click action when the same button was pressed down and released with m_pBtLeftClick() callback.
        //}
        return inside;
    }
    return false;
}

void MouseButton::Draw(SDL_Renderer* renderer)
{
    if (m_pTexture != nullptr)
    {
        m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight);
    }

    if (m_pFont != nullptr)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid(m_pFont, m_text.c_str(), m_textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect;
        textRect.x = m_position.x + (m_iWidth - textSurface->w) / 2;
        textRect.y = m_position.y + (m_iHeight - textSurface->h) / 2;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void MouseButton::SetOnClick(std::function<void(void)> pBtClick)
{
    m_pBtClick = pBtClick;
}

void MouseButton::SetText(std::string text)
{
    m_text = text;
}
