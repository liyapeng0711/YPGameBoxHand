#pragma once
#include "Animation.h"
#include "Weapon.h"
#include <memory>

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
	void DrawGhost(Graphics& gfx)const;
	void ActivateEffect();
	void Fire();
	bool IsAlive()const;
	void BeDead();
	RectF GetRect()const;
	bool AttackCharacter(const RectF& rect);
private:
	VecF pos;
	VecF vel = { 0.0f,0.0f };
	float speed = 160.0f;
	std::vector<Animation> animations;
	Surface sprite;
	Sequence iCurSequence = Sequence::StandingDown;
	// effect
	static constexpr float effectDuration = 0.045f;
	float effectTime = 0.0f;
	bool effectActive = false;
	Color effectColor = Colors::Red;
	// weapon
	size_t weaponNum = 10;
	std::vector<Weapon> weaponOut;
	const float firePeriod = 0.5f;
	float firePeriodCounter = firePeriod;
	VecF weaponDir = { 0.0f, 1.0f }; // in line with StandingDown
	// status
	bool isAlive = true;
};