#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class Mesh;
class GeometryInstanceComponent;
/*
@file LightObject.h
@brief ���C�g�I�u�W�F�N�g(�u��)�̐����ƍX�V�������s��
*/
class LightObject :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	@param	�E���ɓY�킹�邩�ǂ���
	*/
	LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,bool _isRight);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~LightObject()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 3D���f���̕`����s���N���X
	Mesh* mesh;
	GeometryInstanceComponent* geometryInstanceComponent;
	// X���̂��炷�萔�l
	const float ShiftPositionX;
	// �E���ɓY�킹��ꍇ��Y�������炷�萔�l
	const float ShiftRightPositionY;
	// �E���ɓY�킹��ꍇ��Y�������炷�萔�l
	const float ShiftLeftPositionY;
	// Z���̂��炷�萔�l
	const float ShiftPositionZ;

};

