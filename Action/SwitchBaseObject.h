#pragma once
#include "GameObject.h"

class BoxCollider;
class Mesh;
class MeshComponent;

/*
@file SwitchBaseObject.h
@brief Switch�̓y��̐������s��
*/
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
	
	/*
	@fn �X�V����
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;
	// 3D���f���̕`����s���N���X
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	// �����蔻����s���N���X
	Mesh* mesh;


};

