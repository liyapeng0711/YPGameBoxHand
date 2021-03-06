#include "Character.h"

Character::Character(const VecF & pos)
	:
	sprite("Images\\link90x90.bmp"),
	pos(pos)
{
	for (int i = 0; i< int(Sequence::StandingLeft); ++i)
	{
		animations.emplace_back(Animation(90, 90 * i, 90, 90, 4, sprite, 0.16f));
	}
	for (int i = int(Sequence::StandingLeft); i< int(Sequence::Count); ++i)
	{
		animations.emplace_back(Animation(0, 90 * (i- int(Sequence::StandingLeft)), 90, 90, 1, sprite, 0.16f));
	}
}

void Character::Update(float dt)
{
	pos += vel*dt;
	animations[int(iCurSequence)].Update(dt);
	if (effectActive)
	{
		effectTime += dt;
		if (effectTime > effectDuration)
		{
			effectActive = false;
		}
	}
}

void Character::SetDirection(const VecF & dir)
{
	if (dir.x > 0)
	{
		iCurSequence = Sequence::WalkingRight;
	}
	else if (dir.x < 0)
	{
		iCurSequence = Sequence::WalkingLeft;
	}
	else if (dir.y > 0)
	{
		iCurSequence = Sequence::WalkingDown;
	}
	else if (dir.y < 0)
	{
		iCurSequence = Sequence::WalkingUp;
	}
	else
	{
		if (vel.x > 0)
		{
			iCurSequence = Sequence::StandingRight;
		}
		else if (vel.x < 0)
		{
			iCurSequence = Sequence::StandingLeft;
		}
		else if (vel.y > 0)
		{
			iCurSequence = Sequence::StandingDown;
		}
		else if (vel.y < 0)
		{
			iCurSequence = Sequence::StandingUp;
		}
	}
	vel = dir.GetNormalized()*speed;
}

void Character::Draw(Graphics & gfx) const
{
	if (effectActive)
		animations[int(iCurSequence)].DrawColor(VecI(pos), gfx, effectColor);
	else
		animations[int(iCurSequence)].Draw(VecI(pos), gfx);
}

void Character::DrawGhost(Graphics & gfx) const
{
	animations[int(iCurSequence)].DrawGhost(VecI(pos), gfx);
}

void Character::ActivateEffect()
{
	effectActive = true;
	effectTime = 0;
}
