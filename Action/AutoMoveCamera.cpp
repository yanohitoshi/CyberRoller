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
#include "CameraObjectStateLandscape.h"
#include "CameraObjectStateDance.h"
#include "CameraObjectStateGameOver.h"
#include "CameraObjectStateSceneClear.h"

AutoMoveCamera::AutoMoveCamera(const Vector3 _pos, PlayerObject* _playerObject)
	: CameraObjectBase(false, Tag::CAMERA)
{
	// �����o�[�ϐ��̏�����
	SetPosition(_pos);

	forwardVec = Vector3::UnitX;
	tmpMovePos = Vector3::Zero;
	lerpObjectPos = Vector3::Zero;
	// �v���C���[�̃|�C���^��ۑ�
	playerObject = _playerObject;

	AddStatePoolMap(new CameraObjectStateNormal(), CameraState::NORMAL);
	AddStatePoolMap(new CameraObjectStateLandscape(), CameraState::LANDSCAPE);
	AddStatePoolMap(new CameraObjectStateDance(), CameraState::DANCE);
	AddStatePoolMap(new CameraObjectStateGameOver(), CameraState::GAMEOVER);
	AddStatePoolMap(new CameraObjectStateSceneClear(), CameraState::SCENECLEAR);

	nowState = CameraState::NORMAL;
	nextState = CameraState::NORMAL;
}

AutoMoveCamera::~AutoMoveCamera()
{
	RemoveStatePoolMap(CameraState::NORMAL);
	RemoveStatePoolMap(CameraState::LANDSCAPE);
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
}

void AutoMoveCamera::GameObjectInput(const InputState& _keyState)
{
}