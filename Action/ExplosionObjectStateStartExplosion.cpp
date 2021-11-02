#include "ExplosionObjectStateStartExplosion.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateStartExplosion::Update(ExplosionObject* _owner, float _deltaTime)
{
	++explosionStart;

	if (explosionStart > 180)
	{
		_owner->SetIsStartExplosion(false);
		state = ExplosionObjectState::EXPLOSION;
	}

	if (!isHitJumpAttackPlayer)
	{
		VerticalMove(_owner, _deltaTime);
	}
	else
	{
		velocity = blowAwayDirection * 1000.0f;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	Flashing();


	return state;
}

void ExplosionObjectStateStartExplosion::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::EXPLOSION_START;
	meshComponent = _owner->GetMeshComponent();
	// ‘¬“x‚ð‰Šú‰»
	velocity = Vector3::Zero;

	isHitJumpAttackPlayer = _owner->GetIsHitJumpAttackPlayer();

	blowAwayDirection = _owner->GetPosition() - _owner->GetHitPosition();
	blowAwayDirection.Normalize();
	blowAwayDirection.z = 0.0f;
	isRed = false;
	colorChangeTime = 15;
	explosionStart = 0;
	_owner->SetState(State::Disabling);

}

void ExplosionObjectStateStartExplosion::Flashing()
{

	if (explosionStart > 120)
	{
		colorChangeTime = 7;
	}

	if (explosionStart % colorChangeTime == 0)
	{
		if (isRed)
		{
			isRed = false;
		}
		else
		{
			isRed = true;
		}
	}

	if (isRed)
	{
		meshComponent->SetEmissiveColor(EmissiveColorRed);
	}
	else
	{
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
	}
}
