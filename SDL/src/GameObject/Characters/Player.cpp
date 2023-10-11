#include "Player.h"

 Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture,  spriteRow,  frameCount,  numAction,  frameTime)
{
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
}
Player::~Player()
{

}

void Player::Init()
{

}

void	Player::Update(float deltatime, KeySet keyPress) {
	UpdatePos(deltatime, keyPress);
	UpdateAnimation(deltatime);
};
void	Player::UpdatePos(float deltatime, KeySet keyPress) {
	if (keyPress.Left) {
		MoveLeft(deltatime);
	}
	if (keyPress.Down) {
		MoveDown(deltatime);
	}
	if (keyPress.Right) {
		MoveRight(deltatime);
	}
	if (keyPress.Up) {
		MoveTop(deltatime);
	}
};