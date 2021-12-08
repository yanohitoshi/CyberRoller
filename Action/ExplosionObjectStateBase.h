#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectBase.h"

// �N���X�̑O���錾
class MeshComponent;
class SoundEffectComponent;

/*
@enum�@ExplosionObjectState �������̃X�e�[�^�X���ʗp
*/
enum class ExplosionObjectState
{
	// �ҋ@���
	IDLE = 0,
	// �������
	FALL,
	// �������
	EXPLOSION,
	// �_�ŏ��
	EXPLOSION_START,
	// ���A�ҋ@
	RESPAWN,
	// �X�e�[�g�̑���
	NUM,
};

/*
@file ExplosionObjectStateBase.h
@brief ��������I�u�W�F�N�g�̏�ԊǗ��N���X�̊��N���X
*/
class ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateBase()
	: VerticalMoveSpeed(200.0f)
	, EmissiveColorRed(Color::Red)
	, EmissiveColorBlue(Color::LightBlue)
	, OriginalScale(0.5f)
	, SubScale(0.5f)
	, RespownTime(240)
	, ChangeRateTime(45)
	, SecondColorChangeTime(7)
	, ThirdColorChangeTime(3)
	, FirstChangeRateTime(60)
	, SecondChangeRateTime(120) {};

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~ExplosionObjectStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	virtual ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime) = 0;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(ExplosionObjectBase* _owner, float _deltaTime) {};

	/*
	@fn �O���x�N�g����p���ăL�����N�^�[����]������֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_forward ���̃t���[���̑O���x�N�g��
	@param	_tmpForward �O�̃t���[���̑O���x�N�g��
	*/
	void RotationProcess(ExplosionObjectBase* _owner,float _angle, Vector3 _axis);
	
	/*
	@fn �����ړ�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void VerticalMove(ExplosionObjectBase* _owner, float _deltaTime);

protected:

	// �e�N���X�̃|�C���^���i�[���邽�߂�SkeletalMeshComponent�̃|�C���^�ϐ�
	MeshComponent* meshComponent;
	// state�̑J�ڂ��s�����߂̕ϐ�
	ExplosionObjectState state;

	// �T�E���h�G�t�F�N�g�N���X
	SoundEffectComponent* soundEffectComponent;

	// ���x���|�W�V�����ɍ�p���鑬�x���i�[���邽�߂�Vector3�ϐ�
	Vector3 velocity;
	// ���x���i�[���邽�߂̕ϐ�
	float moveSpeed;

	// �t���[�����J�E���g����ϐ�
	int frameCount;
	// �ړ����鑬�x�Ɋ|����{��
	float rate;
	// �p�x
	float angle;

	// ���[�g��ύX����^�C�~���O
	const int ChangeRateTime;

	// �c�ړ�����ۂ̈ړ����x�萔
	const float VerticalMoveSpeed;

	// �G�~�b�V�u�̐F���(��)
	const Vector3 EmissiveColorRed;
	// �G�~�b�V�u�̐F���(��)
	const Vector3 EmissiveColorBlue;

	// ����scale�l
	const float OriginalScale;
	// scale�̌��Z�l
	const float SubScale;

	// ���X�|�[������܂ł̎���
	const int RespownTime;

	// ��Ԗڂ̐F��ς���^�C�~���O
	const int SecondColorChangeTime;
	// �O�Ԗڂ̐F��ς���^�C�~���O
	const int ThirdColorChangeTime;

	// �ŏ��̐F��ς���^�C�~���O��ύX���鎞��
	const int FirstChangeRateTime;
	// ��Ԗڂ̐F��ς���^�C�~���O��ύX���鎞��
	const int SecondChangeRateTime;

private:

};