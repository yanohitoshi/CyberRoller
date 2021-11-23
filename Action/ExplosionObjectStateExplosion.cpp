//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateExplosion.h"
#include "MeshComponent.h"

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
ExplosionObjectState ExplosionObjectStateExplosion::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	++explosionCount;
	if (explosionCount >= ExplosionTime)
	{
		state = ExplosionObjectState::RESPAWN;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ExplosionObjectStateExplosion::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// �X�e�[�^�X�𔚔���ԂɕύX
	state = ExplosionObjectState::EXPLOSION;
	// �ϐ�������
	explosionCount = 0;
	meshComponent = _owner->GetMeshComponent();
	meshComponent->SetVisible(false);
	_owner->SetIsStartExplosion(false);
	_owner->SetIsExplode(true);
}