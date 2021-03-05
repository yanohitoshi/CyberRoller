#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file WallBlockObject.h
@brief ��object�̐������s��
*/

class WallBlockObject : public GameObject
{
public:
	
	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	WallBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	~WallBlockObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	Mesh* mesh;

};
