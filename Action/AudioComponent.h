#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Component.h"
#include <String>

/*
@file AudioComponent.h
@brief Component�N���X���p�������I�[�f�B�I�֘AComponent�N���X�̊��̃N���X
*/
class AudioComponent :
    public Component
{
public:

	/*
	@brief	�R���X�g���N�^
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�ǂݍ��ރT�E���h�t�@�C���̃p�X
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	AudioComponent(GameObject* _owner, const std::string& _fileName,int _updateOrder = 200);

	/*
	@brief	�f�X�g���N�^
	*/
	~AudioComponent()override {};

protected:

	// �����̃T�E���h�̃t�@�C���l�[��
	std::string myFileName;

public: // �Q�b�^�[�Z�b�^�[

	/*
	@fn �����̃t�@�C���l�[����getter
	@return �����̃t�@�C���l�[����Ԃ�
	*/
	const std::string& GetFileName() { return myFileName; }

};