#include "Monster.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Monster3.h"
#include "Monster4.h"
#include "Define.h"
#include "cmath"
#define ATTACK_DISTANCE 192
#define ONE_RAD 180


Monster::Monster(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_speed = 90;
	m_iWidth = 64;
	m_iHeight = 64;
	m_pIsHidden = false;
	m_angle = 0;
}

Monster::~Monster()
{
	printf("huy doi tuong monster\n");
}

std::shared_ptr<TextureManager> Monster::textureMonster1;
std::shared_ptr<TextureManager> Monster::textureMonster2;
std::shared_ptr<TextureManager> Monster::textureMonster3;
std::shared_ptr<TextureManager> Monster::textureMonster4;

void Monster::Init()
{
	textureMonster1 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster1.png");
	textureMonster2 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster2.png");
	textureMonster3 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster3.png");
	textureMonster4 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster4.png");
}

void Monster::Update(float deltatime, Vector2 playerPos) {

	SetSpeed(playerPos);
	SetVelocity(playerPos);
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
};
void Monster::UpdatePos(float deltatime)
{
	m_position.x = m_position.x + m_VelocityX * deltatime; 
	m_position.y = m_position.y + m_VelocityY * deltatime;
}

void Monster::SetSpeed(Vector2 playerPos) {
	if (sqrt((pow(abs(m_position.x - playerPos.x), 2) + pow(abs(m_position.y - playerPos.y), 2))) <= ATTACK_DISTANCE) {
		m_speed = 90;
	}
	else {
		m_speed = 0;
	}
}
void Monster::SetVelocity(Vector2 playerPos)
{


	double angleRadians = atan((float)(playerPos.y - m_position.y) / (float)(playerPos.x - m_position.x));

	double angleDegrees = angleRadians * ONE_RAD / M_PI;


	if ((float)(playerPos.x -  m_position.x < 0)) {
		if (playerPos.y - m_position.y  < 0) {
			angleDegrees = angleDegrees - ONE_RAD;
		}
		else {
			angleDegrees = angleDegrees + ONE_RAD;
		}
	}

	m_VelocityX = m_speed  * cos(angleDegrees / ONE_RAD * M_PI);
	m_VelocityY = m_speed  * sin(angleDegrees / ONE_RAD * M_PI);

}
;

std::shared_ptr<Monster> Monster::CreateMonster(MonsterType stt)
{
	std::shared_ptr<TextureManager> texture = nullptr;
	std::shared_ptr<Monster> monster = nullptr;
	switch (stt)
	{
	case MonsterType::MONSTER1:
	{
		std::shared_ptr<TextureManager> textureMonster1 =  ResourceManagers::GetInstance()->GetTexture("Monsters/Monster1.png");
		monster = std::make_shared<Monster1>(textureMonster1, 1, 18, 1, 0.1f);
		break;
	}
	case MonsterType::MONSTER2:
	{
		std::shared_ptr<TextureManager> textureMonster1 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster2.png");
		monster = std::make_shared<Monster2>(textureMonster1, 1, 18, 1, 0.1f);
		break;
	}
	case MonsterType::MONSTER3:
	{
		std::shared_ptr<TextureManager> textureMonster1 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster3.png");
		monster = std::make_shared<Monster3>(textureMonster1, 1, 18, 1, 0.1f);
		break;
	}
	case MonsterType::MONSTER4:
	{
		std::shared_ptr<TextureManager> textureMonster1 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster4.png");
		monster = std::make_shared<Monster4>(textureMonster1, 1, 18, 1, 0.1f);
		break;
	}
	default:
		break;
	}
	return monster;
}
