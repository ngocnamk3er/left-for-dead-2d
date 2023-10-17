#include "Player.h"
#include <cmath>
#include <iostream>
#define ONE_RAD 180

using namespace std;

Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{

}
Player::~Player()
{

}

void Player::Init()
{

}

void	Player::Update(float deltatime, KeySet keyPress, AimMouse aimMouse) {
	UpdatePos(deltatime, keyPress);
	SetGunAngle(aimMouse);
	UpdateAnimation(deltatime);
	m_gun->UpdatePjectile(deltatime);
};

void Player::Draw(SDL_Renderer* renderer)
{
	SpriteAnimation::Draw(renderer);
	DrawGun(renderer);
}
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
	m_gun->SetSize(64, 24);
}
//private
void Player::SetGunAngle(AimMouse aimMouse)
{
	m_gun->Set2DPosition(m_position.x + m_iWidth / 3, m_position.y + m_iHeight / 2);


	double angleRadians = atan((float)(aimMouse.y - (m_position.y + m_iHeight / 2) )/ (float)(aimMouse.x - (m_position.x + m_iWidth / 2)));

	double angleDegrees = angleRadians * ONE_RAD / M_PI;


	if ((float)(aimMouse.x - (m_position.x + m_iWidth / 2)) < 0) {
		if (aimMouse.y - (m_position.y + m_iHeight / 2) < 0) {
			angleDegrees = angleDegrees - ONE_RAD;
		}
		else {
			angleDegrees = angleDegrees + ONE_RAD;
		}
	}

	//printf("%f\n", angleDegrees);
	//printf("%d\n", (aimMouse.y - (m_position.y + m_iHeight / 2)));
	//printf("%d\n", (aimMouse.x - (m_position.x + m_iWidth / 2)));
	//printf("%f\n", angleDegrees);
	m_gun->SetRotation(angleDegrees);
}
void Player::DrawGun(SDL_Renderer* renderer)
{
	m_gun->Draw(renderer);
}
void Player::PullTrigger()
{
	m_gun->Shot();
}
;