//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DebrisEffectObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Mesh.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�N���X�̃|�C���^
@param	�����x�N�g��
*/
DebrisEffectObject::DebrisEffectObject(const Vector3& _pos, const Vector3& _direction)
	: GameObject(false,Tag::GROUND)
	, MovePower(50.0f)
	, MaxLifeCount(60)
	, SpeedRandValue(1500)
	, SpeedLowestValue(1000)
	, RotateRandValue(361)
	, RotateLowestValue(50)
	, FallSpeed(0.05f)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_pos);
	SetScale(Vector3(2.0f,2.0f,2.0f));
	tag = Tag::GROUND;
	state = Active;
	isPushBackToPlayer = false;
	isCheckGroundToPlayer = false;
	isPushBackToCamera = false;

	direction = _direction;
	// �������ԏ�����
	lifeCount = MaxLifeCount;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/Ground/model/debrisGround.gpmesh"));
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	// �����_���ȑ��x�𓾂�
	moveSpeed = (float)(rand() % SpeedRandValue + SpeedLowestValue);

	// �����_���Ȓl�ŉ�]���|����
	Rotation(this, (float)(rand() % RotateRandValue + RotateLowestValue), Vector3::UnitX);
	Rotation(this, (float)(rand() % RotateRandValue + RotateLowestValue), Vector3::UnitY);
	Rotation(this, (float)(rand() % RotateRandValue + RotateLowestValue), Vector3::UnitZ);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
DebrisEffectObject::~DebrisEffectObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void DebrisEffectObject::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ����炷
	LifeCountDown();
	velocity = direction * moveSpeed;
	SetPosition(position + velocity * _deltaTime);

	// z�������x�N�g�����}�C�i�X�����ɂ��Ă���
	direction.z -= FallSpeed;

	// -1.0�ȉ��ɂȂ�����1.0�ŌŒ�
	if (direction.z <= -1.0f)
	{
		direction.z = -1.0f;
	}

	// ���C�t�J�E���g��0�ȉ��ɂȂ�����
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
		SetState(state);
	}
}

/*
@fn �������Ԃ̃J�E���g�_�E��
*/
void DebrisEffectObject::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
	if (lifeCount <= 0)
	{
		meshComponent->SetVisible(false);
		SetState(State::Dead);

	}
	else
	{
		meshComponent->SetVisible(true);
		lifeCount--;
	}
}
