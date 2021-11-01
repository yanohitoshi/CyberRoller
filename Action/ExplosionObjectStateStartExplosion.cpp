#include "ExplosionObjectStateStartExplosion.h"

ExplosionObjectState ExplosionObjectStateStartExplosion::Update(ExplosionObject* _owner, float _deltaTime)
{
	if (!isHitJumpAttackPlayer)
	{
		VerticalMove(_owner, _deltaTime);
	}
	else
	{
		velocity = blowAwayDirection * 100.0f;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	return state;
}

void ExplosionObjectStateStartExplosion::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::EXPLOSION_START;

	isHitJumpAttackPlayer = _owner->GetIsHitJumpAttackPlayer();
	blowAwayDirection = _owner->GetPosition() - _owner->GetHitPosition();
	blowAwayDirection.Normalize();
	blowAwayDirection.z = 0.0f;

}