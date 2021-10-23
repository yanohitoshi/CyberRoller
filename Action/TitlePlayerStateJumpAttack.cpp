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
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->SetVisible(false);

	// owner����owner��meshComponent�̃|�C���^�����炤
	meshComponent = _owner->GetMeshComponent();
	meshComponent->SetVisible(true);

	// state��DEAD��Ԃɂ��ĕۑ�
	state = TitlePlayerState::JUMP_ATTACK;
}
