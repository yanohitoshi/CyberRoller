#include "ExplosionObjectStateStartExplosion.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateStartExplosion::Update(ExplosionObject* _owner, float _deltaTime)
{
	++explosionStart;

	if (explosionStart > 180 || _owner->GetIsHitExplosionObject())
	{
		state = ExplosionObjectState::EXPLOSION;
		return state;
	}

	if (!isHitJumpAttackPlayer)
	{
		VerticalMove(_owner, _deltaTime);
	}
	else
	{
		velocity = blowAwayDirection * BlowAwaySpeed;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
		angle += 0.1;
		RotationProcess(_owner, angle, Vector3::UnitY);
	}

	Flashing();

	return state;
}

void ExplosionObjectStateStartExplosion::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::EXPLOSION_START;
	meshComponent = _owner->GetMeshComponent();
	// ���x��������
	velocity = Vector3::Zero;

	isHitJumpAttackPlayer = _owner->GetIsHitJumpAttackPlayer();

	blowAwayDirection = _owner->GetPosition() - _owner->GetHitPosition();
	blowAwayDirection.Normalize();
	blowAwayDirection.z = 0.0f;
	isRed = false;
	colorChangeTime = FirstColorChangeTime;
	explosionStart = 0;
	angle = 0;
	_owner->SetState(State::Disabling);

}

void ExplosionObjectStateStartExplosion::Flashing()
{

	if (explosionStart > 60)
	{
		colorChangeTime = 7;
	}

	if (explosionStart > 120)
	{
		colorChangeTime = 3;
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