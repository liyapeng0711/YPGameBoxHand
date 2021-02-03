#pragma once
#include "Animation.h"

class Character
{
private:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};
public:
	Character(const VecF& pos);
	void Update(float dt);
	void SetDirection(const VecF& dir);
	void Draw(Graphics& gfx)const;
private:
	VecF pos;
	VecF vel = { 0,0 };
	float speed = 80.0f;
	std::vector<Animation> animations;
	Surface sprite;
	Sequence iCurSequence = Sequence::StandingDown;
};