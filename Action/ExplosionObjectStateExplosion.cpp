//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateExplosion.h"
#include "MeshComponent.h"
#include "SoundEffectComponent.h"

ExplosionObjectStateExplosion::ExplosionObjectStateExplosion(ExplosionObjectBase* _owner)
	: ExplosionTime(10)
{
	soundEffectComponent = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Explosion/Explosion.wav");
}

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

	// ���ʉ���炷
	soundEffectComponent->Play();
}