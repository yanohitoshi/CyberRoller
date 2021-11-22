#include "AutoMoveCamera.h"
#include "Renderer.h"
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

	AddStatePoolMap(new CameraObjectStateNormal(), CameraState::NORMAL);
	AddStatePoolMap(new CameraObjectStateChangeMode(), CameraState::CHANGEMODE);
	AddStatePoolMap(new CameraObjectStateDance(), CameraState::DANCE);
	AddStatePoolMap(new CameraObjectStateGameOver(), CameraState::GAMEOVER);
	AddStatePoolMap(new CameraObjectStateSceneClear(), CameraState::SCENECLEAR);
	AddStatePoolMap(new CameraObjectStateSceneStart(), CameraState::SCENESTART);

	nowState = CameraState::NONE;
	//nextState = CameraState::SCENESTART;
	nextState = CameraState::NORMAL;
}

AutoMoveCamera::~AutoMoveCamera()
{
	RemoveStatePoolMap(CameraState::NORMAL);
	RemoveStatePoolMap(CameraState::CHANGEMODE);
	RemoveStatePoolMap(CameraState::DANCE);
	RemoveStatePoolMap(CameraState::GAMEOVER);
	RemoveStatePoolMap(CameraState::SCENECLEAR);
	ClearStatePoolMap();
}

void AutoMoveCamera::UpdateGameObject(float _deltaTime)
{
	// �v���C���[���_���X��Ԃ�������
	if (playerObject->GetIsDancing())
	{
		// �_���X�J�����ɕύX
		nextState = CameraState::DANCE;
	}

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

	nextState = CameraState::NORMAL;
	offSetPosition = NormalOffset;
}

void AutoMoveCamera::GameObjectInput(const InputState& _keyState)
{
}