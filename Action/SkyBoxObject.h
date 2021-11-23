#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file SkyBoxObject.h
@brief SkyBoxObject�Ǘ��N���X
*/
class SkyBoxObject : public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	*/
	SkyBoxObject(bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~SkyBoxObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn �L���[�u�}�b�vComponent��getter
	@return	cubeMapComp �g�p���Ă���L���[�u�}�b�vComponent��Ԃ�
	*/
	class CubeMapComponent* GetCubeMapComp() { return cubeMapComp; }

private:

	// �L���[�u�}�b�vComponent�N���X�̃|�C���^
	class CubeMapComponent* cubeMapComp;
};