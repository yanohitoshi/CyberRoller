#pragma once
#include "ExplosionObject.h"

class MeshComponent;


/*
@enum�@ExplosionObjectState �������̃X�e�[�^�X���ʗp
*/
enum class ExplosionObjectState
{
	// �ҋ@���
	IDLE = 0,
	// �������
	EXPLOSION,
	// �_�ŏ��
	EXPLOSION_START,
	// ���A�ҋ@
	RESPAWN,
	// �X�e�[�g�̑���
	NUM,
};


class ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateBase()
	: VerticalMoveSpeed(100.0f)
	, EmissiveColorRed(Color::Red)
	, EmissiveColorBlue(Color::LightBlue){};

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~ExplosionObjectStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	virtual ExplosionObjectState Update(ExplosionObject* _owner, float _deltaTime) = 0;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(ExplosionObject* _owner, float _deltaTime) {};

	/*
	@fn �O���x�N�g����p���ăL�����N�^�[����]������֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_forward ���̃t���[���̑O���x�N�g��
	@param	_tmpForward �O�̃t���[���̑O���x�N�g��
	*/
	void RotationProcess(ExplosionObject* _owner,float _angle, Vector3 _axis);

	void VerticalMove(ExplosionObject* _owner, float _deltaTime);

protected:

	// �e�N���X�̃|�C���^���i�[���邽�߂�SkeletalMeshComponent�̃|�C���^�ϐ�
	MeshComponent* meshComponent;
	// state�̑J�ڂ��s�����߂̕ϐ�
	ExplosionObjectState state;
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
	// �c�ړ�����ۂ̈ړ����x�萔
	const float VerticalMoveSpeed;
	const Vector3 EmissiveColorRed;
	const Vector3 EmissiveColorBlue;

private:


};