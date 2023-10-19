#include "Player.h"
#include <cmath>
#include <iostream>
#include <Point.h>
#include "Define.h"

#define ONE_RAD 180

using namespace std;

Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{

}
Player::~Player()
{
	printf("Huy doi truong player\n");
}

void Player::Init()
{

}

void	Player::Update(float deltatime, KeySet keyPress, AimMouse aimMouse, std::vector<std::vector<int>> StaticMap) {
	SetSpeed(keyPress, StaticMap, deltatime);
	UpdatePos(deltatime);
	SetGunAngle(aimMouse);
	UpdateAnimation(deltatime);
	m_gun->UpdatePjectile(deltatime);
};

void Player::Draw(SDL_Renderer* renderer)
{
	SpriteAnimation::Draw(renderer);
	DrawGun(renderer);
}
void	Player::UpdatePos(float deltatime) {
	m_position.x = m_position.x + deltatime * m_pSpeedX;
	m_position.y = m_position.y + deltatime * m_pSpeedY;
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


	double angleRadians = atan((float)(aimMouse.y - (m_position.y + m_iHeight / 2)) / (float)(aimMouse.x - (m_position.x + m_iWidth / 2)));

	double angleDegrees = angleRadians * ONE_RAD / M_PI;


	if ((float)(aimMouse.x - (m_position.x + m_iWidth / 2)) < 0) {
		if (aimMouse.y - (m_position.y + m_iHeight / 2) < 0) {
			angleDegrees = angleDegrees - ONE_RAD;
		}
		else {
			angleDegrees = angleDegrees + ONE_RAD;
		}
	}

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
void Player::HandleCollison(std::vector<std::vector<int>> StaticMap, std::list<std::shared_ptr<Monster>> listMonster, float deltatime)
{
	for each (std::shared_ptr<Monster> monster in listMonster)
	{
		if (!monster->IsHidden()) {
			for each (std::shared_ptr<Projectile> projectile in m_gun->GetListProjectile())
			{
				if (!projectile->IsHidden()) {
					if (sqrt((pow(abs(monster->Get2DPosition().x - projectile->Get2DPosition().x), 2) + pow(abs(monster->Get2DPosition().y - projectile->Get2DPosition().y), 2))) <= 48) {
						monster->SetHidden(true);
						projectile->SetHidden(true);
					}
				}
			}
		}
	}
}
void Player::SetSpeed(KeySet keyPress, std::vector<std::vector<int>> StaticMap, float deltatime)
{
	m_pSpeedX = keyPress.Left * (-90) + keyPress.Right * 90;
	m_pSpeedY = keyPress.Up * (-90) + keyPress.Down * 90;
	if (m_pSpeedX < 0)
	{
		SetFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (m_pSpeedX > 0)
	{
		SetFlip(SDL_FLIP_NONE);
	}

	Point LeftTop = { m_position.x, m_position.y };
	Point RightTop = { m_position.x + m_iWidth, m_position.y };
	Point LeftDown = { m_position.x, m_position.y + m_iHeight };
	Point RightDown = { m_position.x + m_iWidth, m_position.y + m_iHeight };

	float y = m_position.y;

	if (LeftTop.x + m_pSpeedX * deltatime <=  0) {
		m_pSpeedX = 0;
	}
	if (RightTop.x + m_pSpeedX * deltatime >= SCREEN_WIDTH) {
		m_pSpeedX = 0;
	}
	if (LeftTop.y + m_pSpeedY * deltatime <= 0 ) {
		m_pSpeedY = 0;
	}
	if (LeftDown.y + m_pSpeedY * deltatime >= SCREEN_HEIDHT) {
		m_pSpeedY = 0;
	}
	
	if (StaticMap[(int)(LeftTop.y / 64)][(int)((LeftTop.x + m_pSpeedX * deltatime) / 64)] != 15
		|| StaticMap[(int)(RightTop.y / 64)][(int)((RightTop.x + m_pSpeedX * deltatime) / 64)] != 15
		|| StaticMap[(int)(RightDown.y / 64)][(int)((LeftDown.x + m_pSpeedX * deltatime) / 64)] != 15
		|| StaticMap[(int)(RightDown.y / 64)][(int)((RightDown.x + m_pSpeedX * deltatime) / 64)] != 15
		)
	{
		m_pSpeedX = 0;
	}
	if (StaticMap[(int)((LeftTop.y + m_pSpeedY * deltatime) / 64)][(int)((LeftTop.x) / 64)] != 15
		|| StaticMap[(int)((RightTop.y + m_pSpeedY * deltatime) / 64)][(int)((RightTop.x) / 64)] != 15
		|| StaticMap[(int)((LeftDown.y + m_pSpeedY * deltatime) / 64)][(int)((LeftDown.x) / 64)] != 15
		|| StaticMap[(int)((RightDown.y + m_pSpeedY * deltatime) / 64)][(int)((RightDown.x) / 64)] != 15
		)
	{
		m_pSpeedY = 0;
	}
}
