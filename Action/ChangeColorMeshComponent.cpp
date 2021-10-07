//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ChangeColorMeshComponent.h"
#include "MeshComponent.h"
#include "GameObject.h"
#include "Shader.h"
#include "Renderer.h"

/*
@fn �R���X�g���N�^
@param _owner �e�ƂȂ�GameObject�̃|�C���^
@param _skelton �X�P���g���f�[�^��p���邩
@param _color �r���ŐF�̕ύX��p���邩
*/
ChangeColorMeshComponent::ChangeColorMeshComponent(GameObject* _owner, bool _skelton,bool _color)
	:MeshComponent(_owner, _skelton,_color)
{
}

/*
@fn �f�X�g���N�^
@brief  component�̍폜���s��
*/
ChangeColorMeshComponent::~ChangeColorMeshComponent()
{
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void ChangeColorMeshComponent::Draw(Shader* _shader)
{
	// �F���𑗂�
	_shader->SetVectorUniform("uColor", color);
	//�ʏ�̃��b�V���R���|�[�l���g�̕`��
	MeshComponent::Draw(_shader);
}