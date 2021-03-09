#pragma once

#include "GameObject.h"
#include <glew.h>

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
	*/
	SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~SwitchBlock();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	// ��悲�Ƃɕ����ꂽswitch�����ׂĉ����ꂽ���ǂ����`�F�b�N����֐�
	void ChackOnFlag(Tag& _Tag);

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
		�������Ɛڂ��Ă��鎞�ɂ��̑��x�����炤���߂�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;
	
	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
		�v���C���[�̑�������Ƃ�OnCollision
	@param	��������GameObject
	*/
	void PlayerFootOnCollision(const GameObject& _hitObject);

	// �F�ύX�@�\�t��MeshComponent
	ChangeColorMeshComponent* meshComponent;
	// �������Ɛڂ��Ă��鎞�ɂ��̑��x�����炤���߂�Collider
	BoxCollider* boxCollider;
	// �v���C���[�Ƃ̑�������pCollider
	BoxCollider* PlayerFootBoxCollider;
	// ���b�V������AABB�̍ő�_�ŏ��_�𓾂�Ƃ��Ɏg��
	Mesh* mesh;
	// Switch�����p�\��
	bool isAvailableSwitch;
	// Switch�̏����|�W�V�����ۑ��p
	Vector3 initPosition;
	// player��switch�ɏ���Ă��邩�ǂ���
	bool isOnPlayer;
	bool isHitPlayer;
	// �����̂��~�߂邩�ǂ���
	bool pushStop;
	// �F��ς��邩�ǂ���
	bool changeColorFlag;
	// �O�̃t���[���ŐF�ύX���s��ꂽ���ǂ���
	bool tmpChangeColorFlag;
	// switch�̒�~�ʒu
	float stopPoint;

};
