#pragma once
#include "GameObject.h"

class BoxCollider;

class RespawnPoint :
    public GameObject
{
public:
	
	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�����蔻��pAABB
	@param	�I�u�W�F�N�g���ʗptag
	*/
	RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag);
	~RespawnPoint();
	
	/*
	@fn �X�V����
	@param	�t���[�����[�g�Œ�pdeltaTime
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
	// ���X�|�[�����邩�ǂ����t���O
	bool reSpownFlag;
};

