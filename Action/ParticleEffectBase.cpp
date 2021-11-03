//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"

/*
@param _pos �I�u�W�F�N�g�̐����ꏊ
@param _velocity �I�u�W�F�N�g�̈ړ���
@param _lifeCount �I�u�W�F�N�g�̐�������
@param _spriteFileName �摜�ւ̃A�h���X
@param _useStaticBillboardMat StaticBillboardMat���g�p���ĉ�]�v�Z���s�����ǂ���
@param _scale �摜�̊g��T�C�Y(�f�t�H���g�̒l��10)
*/
ParticleEffectBase::ParticleEffectBase(const Vector3& _pos, const Vector3& _velocity, const int& _lifeCount, const std::string& _spriteFileName, bool _useStaticBillboardMat,const float& _scale)
	: GameObject(false,Tag::PARTICLE)
	, lifeCount(_lifeCount)
{
	// �����o�[�ϐ��̏�����
	velocity = _velocity;
	SetPosition(_pos);
	particleComponent = new ParticleComponent(this, _useStaticBillboardMat);
	particleComponent->SetTextureID(RENDERER->GetTexture(_spriteFileName)->GetTextureID());
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particleComponent->SetScale(_scale);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ParticleEffectBase::~ParticleEffectBase()
{
}

/*
@fn �X�V�����֐�
@brief �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
@param	�Ō�̃t���[������������̂ɗv��������
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	// �I�u�W�F�N�g�̍X�V
	UpdateParticleObject(_deltaTime);
	// �|�W�V�����̍X�V
	SetPosition(position + velocity);
}

/*
@fn �h���N���X���ƂɌ��肷��X�V�֐�
*/
void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	// �J�E���g�_�E������
	LifeCountDown();
}

/*
@fn �������Ԃ��J�E���g�_�E������֐��B�h���N���X�ōX�V�֐������肵���ꍇ�����ɒǉ����邱�ƁB
*/
void ParticleEffectBase::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
	if (lifeCount <= 0)
	{
		particleComponent->SetVisible(false);
		SetState(State::Dead);

	}
	else
	{
		particleComponent->SetVisible(true);
		lifeCount--;
	}

}

/*
@fn ��]�v�Z����
@param _axis ��]��
*/
void ParticleEffectBase::Rotation(GameObject* _owner, const float _angle, const Vector3 _axis)
{
	//�����_���Ȓl��]������
	float radian = Math::ToRadians(_angle);
	Quaternion rot = _owner->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	_owner->SetRotation(target);
}