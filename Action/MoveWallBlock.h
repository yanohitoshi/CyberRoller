#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

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
	~MoveWallBlock();
	
	/*
	@fn �X�V����
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	/*
	@fn �X�C�b�`�̏�Ԃ��m�F����֐�
	@param	�ǂ̎�ނ�object�����肷��p��Tag
	@param	�t���[�����[�g�Œ�pdeltaTime
	*/
	void ChackSwitch(Tag& _tag, float _deltaTime);
	
	/*
	@fn �ǂ̕ǂ��ǂ̃X�C�b�`���m�F���邩�Z�b�g����֐�
	@param	�ǂ̎�ނ�object�����肷��p��Tag
	*/
	void SetChackSwitchTag(Tag& _tag);

	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	Mesh* mesh;

	// �����蔻����s���N���X
	BoxCollider* boxCollider;

	//�J���x
	const float moveSpeed;
	//object�̏����ʒu��ۑ�����p��vector
	Vector3 initPos;
	//object�̒�~�ʒu��ۑ�����p��vector
	Vector3 stopPos;
	//open/close����pflag
	bool openFlag;
	// �`�F�b�N����Tag�ۑ��p
	Tag chackTag;
};

