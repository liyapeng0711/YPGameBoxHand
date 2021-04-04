#include "Weapon.h"

Weapon::Weapon(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel.GetNormalized()*speed)
{
}

void Weapon::Update(float dt)
{
	pos += vel*dt;
}

void Weapon::Draw(Graphics & gfx) const
{
	gfx.DrawRect(GetDamageRect(), Colors::White);
}

RectF Weapon::GetDamageRect() const
{
	return RectF::FromCenter(pos, 5.0f, 5.0f);
}
