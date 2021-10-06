#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;

class LightObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,bool _isRight);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~LightObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	MeshComponent* meshComponent;

};

