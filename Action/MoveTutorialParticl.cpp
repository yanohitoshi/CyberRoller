//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MoveTutorialParticl.h"

/*
@brief	�R���X�g���N�^
@param	�|�W�V����
*/
MoveTutorialParticl::MoveTutorialParticl(const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 100, "Assets/Particle/Tutorial/Move/move_tutorial.png", 1.0f)
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
MoveTutorialParticl::~MoveTutorialParticl()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MoveTutorialParticl::UpdateGameObject(float _deltaTime)
{
}