#pragma once
#include "GameObject.h"

// �N���X�̑O�u�錾
class BoxCollider;

class LightPositionChangePoint :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�����蔻��pAABB
	@param	�I�u�W�F�N�g���ʗptag
	*/
	LightPositionChangePoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~LightPositionChangePoint();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;
	// �����蔻����s���N���X
	BoxCollider* boxCollider;
	// ���X�|�[���|�C���g�ƂȂ邩�ǂ����t���O
	bool reSpownFlag;

	const float ShiftPositionZ;
};

