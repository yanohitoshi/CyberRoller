#pragma once
#include "GameObject.h"

class BoxCollider;
class Mesh;
class MeshComponent;

class SwitchBaseObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param  �ǂ̋��̃X�C�b�`�Ȃ̂��𔻕ʂ�����悤��Tag
	*/
	SwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag);
	~SwitchBaseObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	void OnCollision(const GameObject& _hitObject)override;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	Mesh* mesh;


};

