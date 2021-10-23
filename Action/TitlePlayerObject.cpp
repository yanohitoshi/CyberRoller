//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "TitlePlayerStateBase.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ė��p���邩�t���O
@param	�I�u�W�F�N�g���ʗptag
*/
TitlePlayerObject::TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, Gravity (400.0f)
	, MaxFallSpeed(-200.0f)
	, JumpDelayTime(120)
	, JumpSpeed(15.0f)
	, JumpLimitTime(13)
	, OnGroundCoordinate(100.0f)
	, RotationAngle(90.0f)
	, JumpAttackRotationAngle(10.0f)
	, FirstJumpPower(40.0f)
{

	// �|�W�V�������Z�b�g
	SetPosition(_pos);

	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mes h���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/PlayerModel/SK_Rob.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Player/PlayerModel/SK_Rob.gpskel"));
	//���b�V�����擾
	mesh = skeltalMeshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	meshComponent = new MeshComponent(this, false, false);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/JumpAttackPlayerModel/JumpAttackPlayer.gpmesh"));

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	//�A�j���\�V�����p�̉ϒ��z������T�C�Y
	animTypes.resize(TitlePlayerState::STATE_NUM);
	//�A�j���[�V������ǂݍ���
	animTypes[IDLE] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Happy_Idle_Anim.gpanim", true);
	animTypes[RUN] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Running.gpanim", true);
	animTypes[JUMPLOOP] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Floating.gpanim", true);
	animTypes[JUMPSTART] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Jump_up.gpanim", false);
	animTypes[JUMPEND] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Landing.gpanim", false);

	//anim�ϐ��𑬓x0.5f�ōĐ�
	skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);

	// �����o�[�ϐ�������
	//firstJumpPower = 40.0f;
	//jumpPower = firstJumpPower;
	jumpCount = 0;
	// ��]����
	RotationProcess(RotationAngle,Vector3::UnitZ);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TitlePlayerObject::~TitlePlayerObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TitlePlayerObject::UpdateGameObject(float _deltaTime)
{
	// Renderer�Ƀ|�W�V�����𑗂�
	RENDERER->SetPlayerPositon(position);

	// �A�j���[�V������Ԃ̍X�V
	AnimationUpdate();


	//�W�����v���������͗������̎��d�͂�������i��萔�ȏォ��������~�߂Ē萔�ɂ���j
	if (onGround == false && animState != JUMPATTACK)
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

/*
@fn ��]�����֐�
*/
void TitlePlayerObject::RotationProcess(float _angle, Vector3 _axis)
{
	//Z����90�x��]������
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
@fn �d�͏����֐�
@param	_deltaTime �O�̃t���[���ł�����������
*/
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

/*
@fn �W�����v�f�B���C�����֐�
*/
void TitlePlayerObject::JumpDelayProcess()
{
	// �W�����v����Ԋu�𐔂���
	++jumpDelayCount;

	// ���Ԃ�������W�����v�����W�����v�J�n�A�j���[�V�������Đ�
	if (jumpDelayCount >= JumpDelayTime)
	{
		// �W�����v�t���O��true��
		jumpFlag = true;
		++jumpCount;
		// �A�j���[�V�����Đ�
		skeltalMeshComponent->PlayAnimation(animTypes[JUMPSTART], 1.0f);
		// �X�e�[�^�X��JUMPSTART�ɕύX
		animState = JUMPSTART;
		// �J�E���g���Z�b�g
		jumpDelayCount = 0;
	}
}

/*
@fn �W�����v�����֐�
*/
void TitlePlayerObject::JumpProcess()
{
	if (animState == JUMPATTACK)
	{
		jumpAttackRotationAngle += JumpAttackRotationAngle;
		RotationProcess(jumpAttackRotationAngle, Vector3::UnitX);
	}
	else
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
}

/*
@fn �ڒn���菈���֐�
*/
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

/*
@fn �A�j���[�V�����̍X�V����
*/
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
		
	}

	// �W�����v���łȂ��A�j���[�V�����X�e�[�^�X��RUN�Ŗ���������
	if (jumpFlag == false && animState != RUN)
	{
		// �����A�j���[�V�����̍Đ����J�n
		skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
		// �X�e�[�^�X��RUN�ɕύX
		animState = RUN;
		return;
	}

	if (animState == JUMPATTACK)
	{
		skeltalMeshComponent->SetVisible(false);
		meshComponent->SetVisible(true);
	}
	else
	{
		skeltalMeshComponent->SetVisible(true);
		meshComponent->SetVisible(false);
	}
}

const Animation* TitlePlayerObject::GetAnimation(TitlePlayerState _state)
{
	// _state�Ԗڂ̃A�j���[�V������Ԃ�
	return animTypes[static_cast<unsigned int>(_state)];
}
