#pragma once
#include "Component.h"
#include <String>

class AudioComponent :
    public Component
{
public:

	/*
	@brief	�R���X�g���N�^
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�Ȃ��Collider�Ȃ̂�����pTag(PhysicsTag)
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	@param  �����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
	*/
	AudioComponent(GameObject* _owner, const std::string& _fileName,int _updateOrder = 200);

	~AudioComponent()override {};

protected:

	// �����蔻����s�����ǂ����̔���pTag
	const std::string& myFileName;

public: // �Q�b�^�[�Z�b�^�[


};