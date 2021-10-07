//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "JumpAttackTutorialParticl.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
*/
JumpAttackTutorialParticl::JumpAttackTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/jump_attack_tutorial.png", true)
	, InitScale(512.0f)
{
	// ParticleComponent������
	particleComponent->SetOffSet(Vector3(0.0f, 0.0f, 0.0f));
	particleComponent->SetVisible(true);
	particleComponent->SetScale(InitScale);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
JumpAttackTutorialParticl::~JumpAttackTutorialParticl()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void JumpAttackTutorialParticl::UpdateGameObject(float _deltaTime)
{
}