#include "Monster.h"
#include "Monster1.h"



Monster::Monster(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime)
{
	m_speed = 200;
	m_iWidth = 64;
	m_iHeight = 64;
}

Monster::~Monster()
{

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

void Monster::Update(float deltatime) {
	UpdatePos(deltatime);
	UpdateAnimation(deltatime);
};
void Monster::UpdatePos(float deltatime)
{
	m_position.x = m_position.x + m_speed *  deltatime; 
}
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
		monster = std::make_shared<Monster1>(textureMonster1, 1, 18, 1, 0.1f);
		break;
	}
	case MonsterType::MONSTER3:
	{
		std::shared_ptr<TextureManager> textureMonster1 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster3.png");
		monster = std::make_shared<Monster1>(textureMonster1, 1, 18, 1, 0.1f);
		break;
	}
	case MonsterType::MONSTER4:
	{
		std::shared_ptr<TextureManager> textureMonster1 = ResourceManagers::GetInstance()->GetTexture("Monsters/Monster4.png");
		monster = std::make_shared<Monster1>(textureMonster1, 1, 18, 1, 0.1f);
		break;
	}
	default:
		break;
	}
	return monster;
}
;