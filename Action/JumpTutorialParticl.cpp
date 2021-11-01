//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "JumpTutorialParticl.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
*/
JumpTutorialParticl::JumpTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/jump_tutorial_A.png",true)
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
JumpTutorialParticl::~JumpTutorialParticl()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void JumpTutorialParticl::UpdateGameObject(float _deltaTime)
{
}