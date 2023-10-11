#include "Player.h"
#include <cmath>

using namespace std;

Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
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

void	Player::Update(float deltatime, KeySet keyPress, AimMouse aimMouse) {
	UpdatePos(deltatime, keyPress);
	UpdateGunPos(aimMouse);
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
}
void Player::SetGun(std::shared_ptr<Gun> gun)
{
	m_gun = gun;
}
void Player::Draw(SDL_Renderer* renderer)
{
	SpriteAnimation::Draw(renderer);
	DrawGun(renderer);
}
//private
void Player::UpdateGunPos(AimMouse aimMouse)
{
	m_gun->Set2DPosition(m_position.x + m_iWidth / 3, m_position.y + m_iHeight / 2);


	double angleRadians = atan((float)(aimMouse.y - (m_position.y + m_iHeight / 2) )/ (float)(aimMouse.x - (m_position.x + m_iWidth / 2)));

	double angleDegrees = angleRadians * 180 / M_PI;

	printf("%f\n", angleDegrees);

	if ((float)(aimMouse.x - (m_position.x + m_iWidth / 2)) < 0) {
		angleDegrees = angleDegrees + 180;
	}

	//printf("%d\n", (aimMouse.y - (m_position.y + m_iHeight / 2)));
	//printf("%d\n", (aimMouse.x - (m_position.x + m_iWidth / 2)));
	m_gun->SetRotation(angleDegrees);
}
void Player::DrawGun(SDL_Renderer* renderer)
{
	m_gun->Draw(renderer);
}
;