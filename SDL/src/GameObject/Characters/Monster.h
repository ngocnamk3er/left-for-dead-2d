#pragma once
#include "SpriteAnimation.h"
#include "GameManager/ResourceManagers.h"
#include "CMath.h"
#include "Hitbox.h"

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
	virtual void Update(float deltatime, Vector2 playerPos, std::vector<std::vector<int>> StaticMap);
	virtual void UpdatePos(float deltatime);
	static std::shared_ptr<Monster> CreateMonster(MonsterType stt);
	float GetDame();
private:
	static std::shared_ptr<TextureManager> Monster::textureMonster1;
	static std::shared_ptr<TextureManager> Monster::textureMonster2;
	static std::shared_ptr<TextureManager> Monster::textureMonster3;
	static std::shared_ptr<TextureManager> Monster::textureMonster4;
protected:
	int m_speed;
	bool m_pIsHidden;
	void SetVelocity(Vector2 playerPos, std::vector<std::vector<int>> StaticMap, float deltatime);
	void SetSpeed(Vector2 playerPos);
	float m_VelocityX;
	float m_VelocityY;
	Hitbox m_pHitbox;
	void UpdateHitbox();
	float m_pDame;
};