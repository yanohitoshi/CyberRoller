//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "TitlePlayerStateBase.h"
#include "TitleJumpAttackPlayerObject.h"
#include "TitlePlayerStateJumpAttack.h"
#include "TitlePlayerStateJumpLoop.h"
#include "TitlePlayerStateJumpStart.h"
#include "TitlePlayerStateRun.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ė��p���邩�t���O
@param	�I�u�W�F�N�g���ʗptag
*/
TitlePlayerObject::TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, InitPosition(_pos)
	, RotationAngle(90.0f)
{
	// �����o�[�ϐ�������
	jumpCount = 0;
	jumpFlag = false;
	// �|�W�V�������Z�b�g
	SetPosition(_pos);

	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mes h���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Player/model/SK_Rob.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERING_OBJECT_MANAGER->CreateSkeleton("Assets/Model/Player/model/SK_Rob.gpskel"));
	//���b�V�����擾
	mesh = skeltalMeshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	//�A�j���\�V�����p�̉ϒ��z������T�C�Y
	animTypes.resize(static_cast<unsigned int>(TitlePlayerState::STATE_NUM));
	//�A�j���[�V������ǂݍ���
	animTypes[static_cast<unsigned int>(TitlePlayerState::RUN)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Player/animation/Running.gpanim", true);
	animTypes[static_cast<unsigned int>(TitlePlayerState::JUMP_LOOP)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Player/animation/Floating.gpanim", true);
	animTypes[static_cast<unsigned int>(TitlePlayerState::JUMP_START)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Player/animation/Jump_up.gpanim", false);

	AddStatePoolMap(new TitlePlayerStateJumpAttack, TitlePlayerState::JUMP_ATTACK);
	AddStatePoolMap(new TitlePlayerStateJumpLoop, TitlePlayerState::JUMP_LOOP);
	AddStatePoolMap(new TitlePlayerStateJumpStart, TitlePlayerState::JUMP_START);
	AddStatePoolMap(new TitlePlayerStateRun, TitlePlayerState::RUN);

	// ��]����
	RotationProcess(RotationAngle,Vector3::UnitZ);

	// �^�C�g���p�W�����v�A�^�b�N�v���C���[��ǉ�
	titleJumpAttackPlayerObject = new TitleJumpAttackPlayerObject(this, Vector3(50.0f, 50.0f, 50.0f), JUMP_ATTACK_PLAYER);

	// �X�e�[�^�X�̏�����
	nowState = TitlePlayerState::STATE_NUM;
	nextState = TitlePlayerState::RUN;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TitlePlayerObject::~TitlePlayerObject()
{
	RemoveStatePoolMap(TitlePlayerState::JUMP_ATTACK);
	RemoveStatePoolMap(TitlePlayerState::JUMP_LOOP);
	RemoveStatePoolMap(TitlePlayerState::JUMP_START);
	RemoveStatePoolMap(TitlePlayerState::RUN);
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TitlePlayerObject::UpdateGameObject(float _deltaTime)
{
	// Renderer�Ƀ|�W�V�����𑗂�
	RENDERING_OBJECT_MANAGER->SetPlayerPositon(position);

	// �X�e�[�g�O������X�e�[�g�ύX�����������H
	if (nowState != nextState)
	{
		//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// �X�e�[�g���s
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		nextState = statePoolMap[nowState]->Update(this, _deltaTime);
	}

	// �X�e�[�g��������X�e�[�g�ύX���������H
	if (nowState != nextState)
	{
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}
		nowState = nextState;
	}
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
@brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
@param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
@param	_stateTag ���ƂȂ�^�O
*/
void TitlePlayerObject::AddStatePoolMap(TitlePlayerStateBase* _state, TitlePlayerState _stateTag)
{
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = statePoolMap.find(_stateTag);

	//����Ƃ�
	if (stateMaps != statePoolMap.end())
	{
		return;
	}
	else //�Ȃ��Ƃ�
	{
		statePoolMap[_stateTag] = _state;
	}
}

/*
@brief �X�e�[�g�v�[���p�}�b�v����X�e�[�g�N���X���폜����֐�
@param	_stateTag ���ƂȂ�^�O
*/
void TitlePlayerObject::RemoveStatePoolMap(TitlePlayerState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief �X�e�[�g�v�[���p�}�b�v���N���A����
*/
void TitlePlayerObject::ClearStatePoolMap()
{
	statePoolMap.clear();
}

/*
@fn Animation��getter�֐�
@param _state ���݂̃v���C���[�̃X�e�[�^�X
@return Animation Animation�N���X�̃|�C���^��Ԃ�
*/
const Animation* TitlePlayerObject::GetAnimation(TitlePlayerState _state)
{
	// _state�Ԗڂ̃A�j���[�V������Ԃ�
	return animTypes[static_cast<unsigned int>(_state)];
}