//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "AudioComponent.h"
#include "GameObject.h"

/*
@brief	�R���X�g���N�^
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	�ǂݍ��ރT�E���h�t�@�C���̃p�X
@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
*/
AudioComponent::AudioComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: Component(_owner, _updateOrder)
	, myFileName(_fileName)
{
}