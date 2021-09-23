//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "Renderer.h"
#include "PlayerObject.h"


TitlePlayerObject::TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, Gravity (400.0f)
	, MaxFallSpeed(-200.0f)
	, JumpDelayTime(120)
	, JumpSpeed(15.0f)
	, JumpLimitTime(13)
	, OnGroundCoordinate(100.0f)
	, RotationAngle(90.0f)
{

	// �|�W�V�������Z�b�g
	SetPosition(_pos);

	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mes h���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/PlayerModel/SK_Rob.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Player/PlayerModel/SK_Rob.gpskel"));

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	//�A�j���\�V�����p�̉ϒ��z������T�C�Y
	animTypes.resize(TitleAnimState::ITEMNUM);
	//�A�j���[�V������ǂݍ���
	animTypes[IDLE] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Happy_Idle_Anim.gpanim", true);
	animTypes[RUN] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Running.gpanim", true);
	animTypes[JUMPLOOP] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Floating.gpanim", true);
	animTypes[JUMPSTART] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Jump_up.gpanim", false);
	animTypes[JUMPEND] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Landing.gpanim", false);

	//anim�ϐ��𑬓x0.5f�ōĐ�
	skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);

	// �����o�[�ϐ�������
	firstJumpPower = 40.0f;
	jumpPower = firstJumpPower;

	RotationProcess();

}

TitlePlayerObject::~TitlePlayerObject()
{

}

void TitlePlayerObject::UpdateGameObject(float _deltaTime)
{
	// Renderer�Ƀ|�W�V�����𑗂�
	RENDERER->SetPlayerPositon(position);

	// �A�j���[�V������Ԃ̍X�V
	AnimationUpdate();


	//�W�����v���������͗������̎��d�͂�������i��萔�ȏォ��������~�߂Ē萔�ɂ���j
	if (onGround == false )
	{
		GravityProcess(_deltaTime);
	}

	// �ڒn��Ԃł��W�����v���Ŗ���������
	if (onGround == true && jumpFlag == false)
	{
		JumpDelayProcess();
	}

	// �W�����v����������
	if(jumpFlag == true)
	{
		JumpProcess();
	}

	// �|�W�V�����ɑ��x��ǉ�
	position = position + velocity * _deltaTime;
	// �|�W�V�������X�V
	SetPosition(position);

	// �ڒn���菈��
	IsGroundingProcess();

}

void TitlePlayerObject::RotationProcess()
{
	//Z����90�x��]������
	float radian = Math::ToRadians(RotationAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

void TitlePlayerObject::GravityProcess(float _deltaTime)
{
	// �d�͂��|����
	velocity.z -= Gravity * _deltaTime;

	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �������x���K��l�ɌŒ肷��
		velocity.z = MaxFallSpeed;
	}
}

void TitlePlayerObject::JumpDelayProcess()
{
	// �W�����v����Ԋu�𐔂���
	++jumpDelayCount;

	// ���Ԃ�������W�����v�����W�����v�J�n�A�j���[�V�������Đ�
	if (jumpDelayCount >= JumpDelayTime)
	{
		// �W�����v�t���O��true��
		jumpFlag = true;
		// �A�j���[�V�����Đ�
		skeltalMeshComponent->PlayAnimation(animTypes[JUMPSTART], 1.0f);
		// �X�e�[�^�X��JUMPSTART�ɕύX
		animState = JUMPSTART;
		// �J�E���g���Z�b�g
		jumpDelayCount = 0;
	}
}

void TitlePlayerObject::JumpProcess()
{
	// �W�����v�͂�ǉ�
	velocity.z = jumpPower;

	// �W�����v���̃J�E���g�𐔂���
	++jumpFrameCount;

	// �W�����v���̃J�E���g���K��l�ȉ���������
	if (jumpFrameCount > 0 && jumpFrameCount < JumpLimitTime)
	{
		// ����ɃW�����v�͂�ǉ�
		jumpPower += JumpSpeed;
	}
	else // �W�����v���̃J�E���g���K��l�ȏゾ������
	{
		// �W�����v�͂������ɖ߂�
		jumpPower = firstJumpPower;
		// �J�E���g���Z�b�g
		jumpFrameCount = 0;
		// �W�����v�t���O��false��
		jumpFlag = false;
	}
}

void TitlePlayerObject::IsGroundingProcess()
{
	// �����蔻��Őݒu������Ă��Ȃ��̂ō��W�Ŕ���
	// ���W���K��l�ȉ���������
	if (position.z <= OnGroundCoordinate)
	{
		// �ڒn��Ԃɂ���
		onGround = true;
		// Z���̑��x��0�ɏ�����
		velocity.z = 0.0f;
	}
	else 	// ���W���K��l�ȏゾ������
	{
		// �ڒn�t���O��false��
		onGround = false;
	}
}

void TitlePlayerObject::AnimationUpdate()
{
	// �ڒn���Ŗ���������
	if (onGround == false)
	{
		// �A�j���[�V�����̍Đ����I����Ă�����
		if (!skeltalMeshComponent->IsPlaying())
		{
			// �W�����v���[�v�A�j���[�V�����̍Đ����J�n
			skeltalMeshComponent->PlayAnimation(animTypes[JUMPLOOP], 1.0f);
			// �X�e�[�^�X��JUMPLOOP�ɕύX
			animState = JUMPLOOP;
		}

		return;
	}

	// �ڒn���łȂ��A�j���[�V�����X�e�[�^�X��RUN�Ŗ���������
	if (jumpFlag == false && animState != RUN)
	{
		// �����A�j���[�V�����̍Đ����J�n
		skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
		// �X�e�[�^�X��RUN�ɕύX
		animState = RUN;
		return;
	}

}
