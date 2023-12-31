#include "Player.h"
#include <cmath>
#include <iostream>
#include <Point.h>
#include "Define.h"
#include "Setting.h"

#define MAX_ATTACK_DISTANCE 320


#define ONE_RAD 180

using namespace std;

Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_pHitbox = { 0,0,0,0 };
	m_pHitbox.width = 36;
	m_pHitbox.height = 52;
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSfx("Data/Sounds/SFX/firegun2.mp3");
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
	UpdateHitbox();
	SetGunAngle(aimMouse);
	UpdateAnimation(deltatime);
	m_gun->UpdatePjectile(deltatime);
	m_gun->UpdateHits(deltatime);
};

void Player::Draw(SDL_Renderer* renderer)
{
	SpriteAnimation::Draw(renderer);
	DrawGun(renderer);
	DrawHealthBar(renderer);

}
void	Player::UpdatePos(float deltatime) {
	m_position.x = m_position.x + deltatime * m_pSpeedX;
	m_position.y = m_position.y + deltatime * m_pSpeedY;
}

void Player::UpdateHitbox()
{
	m_pHitbox.x = m_position.x + 12;
	m_pHitbox.y = m_position.y + 12;
}

void Player::SetGun(std::shared_ptr<Gun> gun)
{
	m_gun = gun;
	m_gun->SetSize(64, 24);
	m_gun->Set2DPosition(m_position.x + m_iWidth / 3, m_position.y + m_iHeight / 2);
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

void Player::DrawHealthBar(SDL_Renderer* renderer)
{
	SDL_Rect rectangle;
	rectangle.x = m_position.x;
	rectangle.y = m_position.y - 6;
	rectangle.w = 64;
	rectangle.h = 6;

	SDL_Rect rectangle2;
	rectangle2.x = m_position.x;
	rectangle2.y = m_position.y - 6;
	rectangle2.w = m_pHealth / 5 * 64;
	rectangle2.h = 6;

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);
	SDL_RenderDrawRect(renderer, &rectangle);
	SDL_RenderFillRect(renderer, &rectangle2);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}


void Player::PullTrigger()
{
	m_gun->Shot();
	if (Setting::sfx) {
		m_Sound->PlaySfx(0, 0);
	}
}
void Player::HandleCollison(std::vector<std::vector<int>> StaticMap, std::list<std::shared_ptr<Monster>> listMonster, std::list<std::shared_ptr<Item>> listItems, float deltatime)
{
	/*for each (std::shared_ptr<Monster> monster in listMonster)
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
	}*/
	for each (std::shared_ptr<Projectile> prjtile in m_gun->GetListProjectile())
	{
		if (!prjtile->IsHidden()) {
			for each (std::shared_ptr<Monster> monster in listMonster)
			{
				if (!monster->IsHidden()) {
					if (sqrt((pow(abs(monster->Get2DPosition().x + 32 - prjtile->Get2DPosition().x - 16), 2) + pow(abs(monster->Get2DPosition().y + 32 - prjtile->Get2DPosition().y - 12), 2))) <= 32) {
						monster->DecreHealth();
						prjtile->SetHidden(true);
						m_gun->AddHit(monster->Get2DPosition().x + 16, monster->Get2DPosition().y + 16);
					}
				}
			}

			if (prjtile->Get2DPosition().x < 0 || prjtile->Get2DPosition().x + prjtile->GetWidth() > SCREEN_WIDTH) {
				prjtile->SetHidden(true);
			}
			else if (prjtile->Get2DPosition().y < 0 || prjtile->Get2DPosition().y + prjtile->GetHeight() > SCREEN_HEIDHT) {
				prjtile->SetHidden(true);
			}
			else if (StaticMap[(int)((prjtile->Get2DPosition().y + prjtile->GetHeight() / 2) / 64)][(int)((prjtile->Get2DPosition().x + prjtile->GetWidth() / 2) / 64)] != 15) {
				prjtile->SetHidden(true);
			}
			else if (sqrt((pow(abs(m_position.x - prjtile->Get2DPosition().x), 2) + pow(abs(m_position.y - prjtile->Get2DPosition().y), 2))) >= MAX_ATTACK_DISTANCE ) {
				prjtile->SetHidden(true);
			}
		}
	}
	for each (std::shared_ptr<Monster> monster in listMonster)
	{
		if (!monster->IsHidden()) {
			if (sqrt((pow(abs(monster->Get2DPosition().x - m_position.x), 2) + pow(abs(monster->Get2DPosition().y - m_position.y), 2))) <= 48) {
				m_pHealth = m_pHealth - monster->GetDame() * deltatime;
			}
		}
	}
	for each (std::shared_ptr<Item> item in listItems)
	{
		if (!item->IsHidden()) {
			//item->SetHidden(true); 
			if (sqrt((pow(abs(item->Get2DPosition().x + item->GetWidth() / 2 - m_position.x - m_iWidth / 2), 2) + pow(abs(item->Get2DPosition().y + item->GetHeight() / 2 - m_position.y - m_iHeight / 2), 2))) <= 32) {
				switch (item->GetItemType()){
				case ItemType::GUN_1: {
					std::shared_ptr<Gun1> m_gun = std::make_shared<Gun1>();
					SetGun(m_gun);
					break;
				}
				case ItemType::GUN_2: {
					std::shared_ptr<Gun2> m_gun = std::make_shared<Gun2>();
					SetGun(m_gun);
					break;
				}
				case ItemType::GUN_3: {
					std::shared_ptr<Gun3> m_gun = std::make_shared<Gun3>();
					SetGun(m_gun);
					break;
				}
				case ItemType::GUN_4: {
					std::shared_ptr<Gun4> m_gun = std::make_shared<Gun4>();
					SetGun(m_gun);
					break;
				}
				default:
					break;
				}
				
				item->SetHidden(true);
	
				//m_gun = std::make_shared<Gun3>();
				//m_player->SetGun(m_gun);
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

	Point LeftTop = { m_pHitbox.x, m_pHitbox.y };
	Point RightTop = { m_pHitbox.x + m_pHitbox.width, m_pHitbox.y };
	Point LeftDown = { m_pHitbox.x, m_pHitbox.y + m_pHitbox.height };
	Point RightDown = { m_pHitbox.x + m_pHitbox.width, m_pHitbox.y + m_pHitbox.height };


	if (LeftTop.x + m_pSpeedX * deltatime <= 0) {
		m_pSpeedX = 0;
	}
	if (RightTop.x + m_pSpeedX * deltatime >= SCREEN_WIDTH) {
		m_pSpeedX = 0;
	}
	if (LeftTop.y + m_pSpeedY * deltatime <= 0) {
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

float Player::GetHealth()
{
	return m_pHealth;
}
