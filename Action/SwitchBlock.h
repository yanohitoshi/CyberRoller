#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include <glew.h>

// �N���X�̑O���錾
class BoxCollider;
class Mesh;
class ChangeColorMeshComponent;

/*
@file SwitchBlock.h
@brief �X�C�b�`�̐����ƍX�V�������s��
*/
class SwitchBlock : public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param	�`���[�g���A���p�X�C�b�`���ǂ����t���O
	*/
	SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag ,bool _isTutorial = false);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~SwitchBlock()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn �������֐�	
	*/
	void MovableProcess();
	
	/*
	@fn �F�ύX����
	*/
	void ColorChangeProcess();
	
	/*
	@fn �F�Z�b�g����
	*/
	void SetColorProcess();

	/*
	@fn �^�O���Ƃ̃X�C�b�`�̏�ԃ`�F�b�N�֐�
	@param _Tag �`�F�b�N����X�C�b�`��Tag
	*/	void CheckOnFlag(Tag& _Tag);

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
		�������Ɛڂ��Ă��鎞�ɂ��̑��x�����炤���߂�
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject,const PhysicsTag _physicsTag)override;
	
	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
		�v���C���[�̑�������Ƃ�OnCollision
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void PlayerFootOnCollision(const GameObject& _hitObject,const PhysicsTag _physicsTag);

	// �F�ύX�@�\�t��MeshComponent
	ChangeColorMeshComponent* meshComponent;
	// �������Ɛڂ��Ă��鎞�ɂ��̑��x�����炤���߂�Collider
	BoxCollider* boxCollider;
	// �v���C���[�Ƃ̑�������pCollider
	BoxCollider* PlayerFootBoxCollider;
	// ���b�V������AABB�̍ő�_�ŏ��_�𓾂�Ƃ��Ɏg��
	Mesh* mesh;
	// Switch�̏����|�W�V�����ۑ��p
	Vector3 initPosition;
	// Switch�����p�\��
	bool isAvailableSwitch;
	// player��switch�ɏ���Ă��邩�ǂ���
	bool isOnPlayer;
	bool isHitPlayer;
	// �����̂��~�߂邩�ǂ���
	bool pushStop;
	// �F��ς��邩�ǂ���
	bool changeColorFlag;
	// �O�̃t���[���ŐF�ύX���s��ꂽ���ǂ���
	bool tmpChangeColorFlag;

	//�`���[�g���A���X�C�b�`���ǂ���
	bool isTutorialSwitch;

	// switch�̒�~�ʒu
	float stopPoint;

	// ��~�|�W�V�������߂邽�߂̒萔
	const float ShiftStopPosition;
	// �㏸���x
	const float MoveUpSpeed;
	// ���~���x
	const float MoveDownSpeed;
	// �S�X�C�b�`��ON�̎��̐F
	const Vector3 AllClearColer;
	// �X�C�b�`��ON�̎��̐F
	const Vector3 OnColor;
	// �X�C�b�`��OFF�̎��̐F
	const Vector3 OffColor;
};
