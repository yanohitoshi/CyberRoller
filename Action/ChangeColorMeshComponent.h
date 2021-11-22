#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MeshComponent.h"
#include "Math.h"

/*
 @file ChangeColorMeshComponent.h
 @brief MeshComponent���p�������Q�[������shader���g�p���ĐF��ύX���邱�Ƃ��ł���Component�N���X
*/
class ChangeColorMeshComponent :
    public MeshComponent
{
public:

    /*
    @fn �R���X�g���N�^
    @param _owner �e�ƂȂ�GameObject�̃|�C���^
    @param _skelton �X�P���g���f�[�^��p���邩
    @param _color �r���ŐF�̕ύX��p���邩
    */
    ChangeColorMeshComponent(GameObject* _owner, bool _skelton, bool _color);
    
    /*
    @fn �f�X�g���N�^
    @brief  component�̍폜���s��
    */
    ~ChangeColorMeshComponent();

    /*
    @brief�@�`�揈��
    @param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
    */
    void Draw(Shader* _shader)override;

private:

    // �F��������Vector3�ϐ�
    Vector3 color;

public:// �Q�b�^�[�Z�b�^�[

    /*
    @brief  color�ϐ���setter
    @param  _color �ύX�������F��RGB(Vector3)
    */
    void SetColor(const Vector3& _color) { color = _color; }
};

