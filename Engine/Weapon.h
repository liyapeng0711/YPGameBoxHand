#pragma once
#include"Graphics.h"

class Weapon
{
public:
	Weapon(const VecF& pos, const VecF& vel);
	void Update(float dt);
	void Draw(Graphics& gfx)const;
private:
	float speed = 300.0f;
	VecF pos;
	VecF vel = { 0,0 };
};
