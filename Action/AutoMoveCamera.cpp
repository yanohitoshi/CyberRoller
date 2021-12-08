//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "AutoMoveCamera.h"
#include "RenderingObjectManager.h"
#include "CameraObjectStateBase.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdlingDance.h"
#include "CameraObjectStateNormal.h"
#include "CameraObjectStateChangeMode.h"
#include "CameraObjectStateDance.h"
#include "CameraObjectStateGameOver.h"
#include "CameraObjectStateSceneClear.h"
#include "CameraObjectStateSceneStart.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
@param	�v���C���[�̃|�C���^
*/
AutoMoveCamera::AutoMoveCamera(const Vector3 _pos, PlayerObject* _playerObject)
	: CameraObjectBase(false, Tag::CAMERA)
	, NormalOffset(Vector3(-600.0f, 0.0f, 500.0f))
{
	// �����o�[�ϐ��̏�����
	SetPosition(_pos);

	forwardVec = Vector3::UnitX;
	tmpMovePos = Vector3::Zero;
	lerpObjectPos = Vector3::Zero;
	offSetPosition = NormalOffset;
	// �v���C���[�̃|�C���^��ۑ�
	playerObject = _playerObject;
	isChangeMode = false;

	// �X�e�[�^�X�N���X�̒ǉ�
	AddStatePoolMap(new CameraObjectStateNormal(), CameraState::NORMAL);
	AddStatePoolMap(new CameraObjectStateChangeMode(), CameraState::CHANGEMODE);
	AddStatePoolMap(new CameraObjectStateDance(), CameraState::DANCE);
	AddStatePoolMap(new CameraObjectStateGameOver(), CameraState::GAMEOVER);
	AddStatePoolMap(new CameraObjectStateSceneClear(), CameraState::SCENECLEAR);
	AddStatePoolMap(new CameraObjectStateSceneStart(), CameraState::SCENESTART);

	// �X�e�[�^�X�ϐ�������
	nowState = CameraState::NONE;
	nextState = CameraState::NORMAL;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
AutoMoveCamera::~AutoMoveCamera()
{
	// Map�̌�Еt��
	RemoveStatePoolMap(CameraState::NORMAL);
	RemoveStatePoolMap(CameraState::CHANGEMODE);
	RemoveStatePoolMap(CameraState::DANCE);
	RemoveStatePoolMap(CameraState::GAMEOVER);
	RemoveStatePoolMap(CameraState::SCENECLEAR);
	ClearStatePoolMap();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void AutoMoveCamera::UpdateGameObject(float _deltaTime)
{

	if (isChangeMode)
	{
		// �_���X�J�����ɕύX
		nextState = CameraState::CHANGEMODE;
	}

	// �v���C���[���_���X��Ԃ�������
	if (playerObject->GetIsDancing())
	{
		// �_���X�J�����ɕύX
		nextState = CameraState::DANCE;
	}

	// �^�C���I�[�o�[�ɂȂ��Ă�����
	if (CountDownFont::GetTimeOverFlag())
	{
		// �Q�[���I�[�o�[�J�����ɕύX
		nextState = CameraState::GAMEOVER;
	}

	if (playerObject->GetClearFlag())
	{
		// �Q�[���I�[�o�[�J�����ɕύX
		nextState = CameraState::SCENECLEAR;
	}

	// �X�e�[�g�O������X�e�[�g�ύX�����������H
	if (nowState != nextState)
	{
		// �}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// �X�e�[�g���s
	// �}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
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

	// ��p�؂�ւ����[�h��true��������
	if (isChangeMode)
	{
		// �����蔻��Ő؂�ւ��邩����𔻒肵�Ă���̂ň�x�ʏ��Ԃɐ؂�ւ���
		isChangeMode = false;
		offSetPosition = NormalOffset;
	}
}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
@param	_keyState ���͏��
*/
void AutoMoveCamera::GameObjectInput(const InputState& _keyState)
{
}