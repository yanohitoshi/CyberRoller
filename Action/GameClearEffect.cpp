//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameClearEffect.h"
#include "FireWorksEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�ړ����x
*/
GameClearEffect::GameClearEffect(const Vector3& _pos, const Vector3& _velocity)
	: ParticleEffectBase(_pos, _velocity, 10, "Assets/Effect/Clear/GameClear.png",true)
	, AddScale(10.0f)
	, SubAlpha(0.05f)
	, InitAlpha(1.0f)
	, InitScale(64.0f)
	, MoveSpeed(400.0f)
{
	// �����o�[�ϐ��̏�����
	scale = InitScale;
	alpha = InitAlpha;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 0.0f));
	speed = MoveSpeed;

	// ���򂳂���G�t�F�N�g�̃}�l�[�W���[�N���X��ǉ�
	new FireWorksEffectManager(this);

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
GameClearEffect::~GameClearEffect()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void GameClearEffect::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ̃J�E���g�_�E��
	ParticleEffectBase::LifeCountDown();

	// ���C�t�J�E���g��0�ȏ�ɂȂ�����
	if (lifeCount >= 0)
	{
		// �萔�𑫂��Ċg��
		scale += AddScale;
		// �萔�������ē���
		alpha -= SubAlpha;

		// scale�l���Z�b�g
		particleComponent->SetScale(scale);
		// alpha�l���Z�b�g
		particleComponent->SetAlpha(alpha);

		// �|�W�V�����ɑ��x��ǉ�
		position += velocity * speed * _deltaTime;
		// �|�W�V�������X�V
		SetPosition(position);
	}

	// ���C�t�J�E���g��0�ȉ��ɂȂ�����
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
	}
}