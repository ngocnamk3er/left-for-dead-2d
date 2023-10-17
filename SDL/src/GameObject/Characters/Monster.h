#pragma once
#include "SpriteAnimation.h"
#include "GameManager/ResourceManagers.h"

class Monster;
enum class MonsterType
{
	MONSTER_INVALID = 0,
	MONSTER1,
	MONSTER2,
	MONSTER3,
	MONSTER4
};

class Monster : public SpriteAnimation {
public:
	Monster(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Monster();
	static void Init();
	virtual void Update(float deltatime);
	virtual void UpdatePos(float deltatime);
	static std::shared_ptr<Monster> CreateMonster(MonsterType stt);
private:
	static std::shared_ptr<TextureManager> Monster::textureMonster1;
	static std::shared_ptr<TextureManager> Monster::textureMonster2;
	static std::shared_ptr<TextureManager> Monster::textureMonster3;
	static std::shared_ptr<TextureManager> Monster::textureMonster4;
protected:
	int m_speed;
};