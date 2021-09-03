#pragma once
#include "Component.h"
#include <string>
#include <vector>

/*
 @file CubeMapComponent.h
 @brief �L���[�u�}�b�v�̊Ǘ��ƕ`����s��
*/
class CubeMapComponent :
    public Component
{
public:

	/*
	@fn �R���X�g���N�^
	@param _owner �e�N���X�̃|�C���^
	*/
	CubeMapComponent(class GameObject* _owner);

	/*
	@fn �f�X�g���N�^
	@brief  Component�̍폜���s��
	*/
	~CubeMapComponent();

	/*
	@brief�@texture��������
	@param	in_filePath �g�p����texture�̃t�@�C���p�X
	*/
	void CreateTexture(const std::string& in_filePath);

	/*
	@brief�@�`�揈��
	@param	in_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* in_shader);

	/*
	@brief�@�X�J�C�{�b�N�X�Ɏg�p���Ă���texture��getter
	@param	texture �g�p���Ă���texture�N���X�̃|�C���^
	*/
	class Texture* GetSkyBoxTexture() { return texture; }

	// �L���[�u��\�����邩���Ȃ����̃Z�b�g
	void SetIsVisible(bool in_visible) { isVisible = in_visible; }

	// �P�x���̃Z�b�g
	void SetLuminance(float in_luminance) { luminance = in_luminance; }


private:

	// texture�N���X�̃|�C���^
	class Texture* texture;

	// �P�x���
	float luminance;

	// �`�悷�邩���Ȃ����̃t���O
	bool isVisible;

};

