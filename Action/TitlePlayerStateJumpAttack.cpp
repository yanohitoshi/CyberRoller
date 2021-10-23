#include "TitlePlayerStateJumpAttack.h"
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"

TitlePlayerState TitlePlayerStateJumpAttack::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	rotationAngle += JumpAttackRotationAngle;
	_owner->RotationProcess(rotationAngle,Vector3::UnitX);
	++frameCount;

	if (JumpAttackTime <= frameCount)
	{
		state = TitlePlayerState::JUMP_LOOP;
	}

    return state;
}

void TitlePlayerStateJumpAttack::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->SetVisible(false);

	// ownerからownerのmeshComponentのポインタをもらう
	meshComponent = _owner->GetMeshComponent();
	meshComponent->SetVisible(true);

	// stateをDEAD状態にして保存
	state = TitlePlayerState::JUMP_ATTACK;
}
