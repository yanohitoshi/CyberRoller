#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class BoxCollider;
class Mesh;
class GeometryInstanceComponent;

/*
@file MoveWallBlock.h
@brief �����ǂ̐����ƍX�V�������s��
*/
class MoveWallBlock : public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param	�������x
	@param	�~�܂�ʒu
	*/
	MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,float _speed,Vector3 _stopPos);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~MoveWallBlock()override;
	
	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	/*
	@fn �ǂ��J���֐�
	@brief	�ǂ��J���������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void OpenWall(float _deltaTime);

	/*
	@fn �X�C�b�`�̏�Ԃ��m�F����֐�
	@param	�ǂ̎�ނ�object�����肷��p��Tag
	@param	�t���[�����[�g�Œ�pdeltaTime
	*/
	void CheckSwitch(Tag& _tag);
	
	/*
	@fn �ǂ̕ǂ��ǂ̃X�C�b�`���m�F���邩�Z�b�g����֐�
	@param	�ǂ̎�ނ�object�����肷��p��Tag
	*/
	void SetCheckSwitchTag(Tag& _tag);

	// 3D���f���̕`����s���N���X
	Mesh* mesh;
	GeometryInstanceComponent* geometryInstanceComponent;

	// �����蔻����s���N���X
	BoxCollider* boxCollider;

	// �J���x�萔
	const float MoveSpeed;
	// Y���������炵�ĕǂ𒆐S�Ɉʒu�Â��邽�߂̒萔
	const float ShiftPositionY;

	// object�̏����ʒu��ۑ�����p��vector
	Vector3 initPos;
	// object�̒�~�ʒu��ۑ�����p��vector
	Vector3 stopPos;

	// �`�F�b�N����Tag�ۑ��p
	Tag checkTag;

	// open/close����pflag
	bool openFlag;

public: // �Q�b�^�[�E�Z�b�^�[

	/*
	@fn openFlag��getter�֐�
	@return	openFlag open/close����pFlag
	*/
	bool GetOpenFlag() { return openFlag; }
};

