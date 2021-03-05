#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class PushBoxObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param  �ǂꂭ�炢�̋��������̂�
	@param�@�ǂ̕����ɓ����̂�
	@param�@���x
	@param�@�߂�ۂɑ��x�𗎂Ƃ�����
	@param�@�ǂ̕����ɓ����̂����ʂ��邽�߂̃^�O
	*/
	PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed , MoveDirectionTag _moveTag);
	~PushBoxObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;

};

