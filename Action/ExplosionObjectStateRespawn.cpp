//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
ExplosionObjectState ExplosionObjectStateRespawn::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ���Ԍv��
	++respawnCount;

	// ���Ԃ�������
	if (respawnCount > RespownTime)
	{
		//������
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetVisible(true);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		_owner->SetRotation(Quaternion::Identity);
		_owner->SetScaleZ(5.0f);
		_owner->SetPosition(firstPosition);
		// �X�e�[�^�X���A�C�h�����O��
		state = ExplosionObjectState::IDLE;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ExplosionObjectStateRespawn::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X�����X�|�[����ԂɑJ��
	state = ExplosionObjectState::RESPAWN;
	// �ϐ�������
	firstPosition = _owner->GetFirstPosition();
	respawnCount = 0;
	meshComponent = _owner->GetMeshComponent();
	_owner->SetIsExplode(false);
	_owner->SetState(State::Disabling);
}