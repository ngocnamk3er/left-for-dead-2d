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
	if (StaticMap[(int)((m_position.y + m_pSpeedY * deltatime) / 64)][(int)((m_position.x + m_pSpeedX * deltatime) / 64)] != 15
		|| StaticMap[(int)(m_position.y + m_pSpeedY * deltatime + m_iWidth) / 64][(int)(m_position.x + m_pSpeedX * deltatime) / 64] != 15
		|| StaticMap[(int)(m_position.y + m_pSpeedY * deltatime) / 64][(int)(m_position.x + m_pSpeedX * deltatime + m_iHeight) / 64] != 15
		|| StaticMap[(int)(m_position.y + m_pSpeedY * deltatime + m_iWidth) / 64][(int)(m_position.y + m_pSpeedY * deltatime + m_iHeight) / 64] != 15
		) {
		m_pSpeedX = 0;
		m_pSpeedY = 0;
	}
	printf("---------------%d-----------\n", StaticMap[(int)((m_position.y + m_pSpeedY) / 64)][(int)((m_position.x + m_pSpeedX) / 64)]);
	printf("---------------%d--%d---------\n", (int)((m_position.y + 0) / 64),(int)((m_position.x + 0) / 64));
}
void Player::SetSpeed(KeySet keyPress, std::vector<std::vector<int>> StaticMap, float deltatime)
{
	m_pSpeedX = keyPress.Left * (-90) + keyPress.Right * 90;
	m_pSpeedY = keyPress.Up * (-90) + keyPress.Down * 90;
	if (StaticMap[(int)((m_position.y + m_pSpeedY * deltatime) / 64)][(int)((m_position.x + m_pSpeedX * deltatime) / 64)] != 15
		|| StaticMap[(int)(m_position.y + m_pSpeedY * deltatime + m_iWidth) / 64][(int)(m_position.x + m_pSpeedX * deltatime) / 64] != 15
		|| StaticMap[(int)(m_position.y + m_pSpeedY * deltatime) / 64][(int)(m_position.x + m_pSpeedX * deltatime + m_iHeight) / 64] != 15
		|| StaticMap[(int)(m_position.y + m_pSpeedY * deltatime + m_iWidth) / 64][(int)(m_position.y + m_pSpeedY * deltatime + m_iHeight) / 64] != 15
		) {
		m_pSpeedX = 0;
		m_pSpeedY = 0;
	}
}
