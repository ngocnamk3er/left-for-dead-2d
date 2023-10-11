#include "GameObject/SpriteAnimation.h"


class Monster : public SpriteAnimation {
public:
	Monster(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Monster();
	void	Init() override;
	void	Update(float deltatime);
	void	UpdatePos(float deltatime);
};