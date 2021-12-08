//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CollectionEffectManager.h"
#include "CollectionObject.h"
#include "CollectionRipplesEffect.h"
#include "CollectionLightEffect.h"
#include "CrystalEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�e�N���X�̃|�C���^
*/
CollectionEffectManager::CollectionEffectManager(CollectionObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, LightEffectRandValue(100)
	, MaxLightEffects(24)
	, TowFrequency(2)
	, ThreeFrequency(3)
	, RandValue(100)
	, ActiveTime(30)
{
	// �����o�[�ϐ��̏�����	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
	colorNum = 0;
	activeCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CollectionEffectManager::~CollectionEffectManager()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionEffectManager::UpdateGameObject(float _deltaTime)
{
	// �e�N���X�̃X�e�[�^�X��Active��������
	if (owner->GetIsCollected())
	{
		// particleState��L����
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleState�𖳌���
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// �p�[�e�B�N���̏�Ԃ�����
	switch (particleState)
	{
	case (PARTICLE_DISABLE):
		// ������
		generateFlag = true;
		break;

		// �L����Ԃ�������
	case PARTICLE_ACTIVE:

		ActiveEffect(_deltaTime);
		break;
	}
}

/*
@fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionEffectManager::ActiveEffect(float _deltaTime)
{
	// �����t���O��true�̎�
	if (generateFlag)
	{
		CreationRipplesEffect();
		// �����t���O��false�ɕύX
		generateFlag = false;
	}

	// �J�E���g�𐔂���
	++activeCount;

	// �G�t�F�N�g��Active�ƂȂ��Ă����鎞�ԓ���������
	if (activeCount < ActiveTime)
	{
		CreationLightEffect();
	}
}

/*
@fn �g��G�t�F�N�g���Y�����֐�
*/
void CollectionEffectManager::CreationRipplesEffect()
{
	// �I�[�i�[�̃|�W�V�����擾
	effectPosition = owner->GetPosition();
	new CollectionRipplesEffect(this, effectPosition, Vector3::Zero);
}

/*
@fn ���G�t�F�N�g���Y�����֐�
*/
void CollectionEffectManager::CreationLightEffect()
{
	// �G�t�F�N�g�̐F���ϐ�
	CrystalColor color = CrystalColor::WHITE;

	// �F�ԍ��ɉ����ĐF����ύX
	if (colorNum == CrystalColor::WHITE)
	{
		color = CrystalColor::WHITE;
	}
	else if (colorNum == CrystalColor::RED)
	{
		color = CrystalColor::RED;
	}
	else if (colorNum == CrystalColor::BLUE)
	{
		color = CrystalColor::BLUE;
	}
	else if (colorNum == CrystalColor::GREEN)
	{
		color = CrystalColor::GREEN;
	}

	// �F�ԍ���i�߂�
	++colorNum;

	// �F�ԍ������ɂȂ�����
	if (colorNum >= CrystalColor::NONE)
	{
		// �ԍ���������Ԃɖ߂�
		colorNum = 0;
	}

	// �����_���Ȓl�𐶐�
	Vector3 randDir((float)(rand() % RandValue), (float)(rand() % RandValue), 1.0f);
	randDir.Normalize();

	if (activeCount % TowFrequency == 0)
	{
		randDir.x *= -1.0f;
	}
	
	if (activeCount % ThreeFrequency == 0)
	{
		randDir.y *= -1.0f;
	}

	randDir.z = 1.0f;

	new CollectionLightEffect(this, effectPosition, randDir, color);
}
