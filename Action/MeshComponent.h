#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Component.h"
#include "Math.h"

// �N���X�̑O���錾
class GameObject;
class Shader;
class Mesh;

/*
 @file MeshComponent.h
 @brief ���b�V���f�[�^�̊Ǘ��ƕ`����s��
*/
class MeshComponent : public Component
{
public:

	/*
	@fn �R���X�g���N�^
	@param _skelton �X�P���g���f�[�^��p���邩�B
	@param _color �r���ŐF�̕ύX��p���邩�B
	*/
    MeshComponent(GameObject* _owner,bool _skelton,bool _color);
	
	/*
	@fn �f�X�g���N�^
	@brief  Component�̍폜���s��
	*/
    ~MeshComponent();

	/*
	@brief�@�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
    virtual void Draw(Shader* _shader);

protected:

	//���b�V���f�[�^�N���X�ւ̃|�C���^
    Mesh* mesh;
	//�e�N�X�`���T�C�Y
    size_t textureIndex;
	//�`������邩�ǂ���
	bool visible;
	//�X�P���g���f�[�^��p���邩
	bool isSkelton;
	//�J���[�`�F���W��p���邩
	bool isColorChange;
	// �P�x
	float luminance;
	// �F���
	Vector3 emissiveColor;
	/*
	@brief�@�g�p����texture���Z�b�g����
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	virtual void SetTextureToShader(Shader* _shader);

public: //�Q�b�^�[�Z�b�^�[

	/*
	@brief�@���b�V���R���|�[�l���g���g��Mesh�̐ݒ�
	@param	_mesh �ݒ肷��Mesh�N���X�̃|�C���^
	*/
	virtual void SetMesh(Mesh* _mesh) { mesh = _mesh; }

	/*
	@return �ݒ肳�ꂽMesh�N���X�̃|�C���^
	*/
	virtual Mesh* GetMesh() { return mesh; }

	void SetEmissiveColor(Vector3 _emissiveColor) { emissiveColor = _emissiveColor; }

	/*
	@brief�@���b�V���R���|�[�l���g���g��Texture�C���f�b�N�X�̐ݒ�
	*/
	void SetTextureIndex(size_t _index) { textureIndex = _index; }

	/*
	@brief�@�`������邩�ǂ�����ݒ�
	@param	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/*
	@brief�@�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	bool GetVisible() const { return visible; }

	/*
	@return �X�P���g���f�[�^��p���邩
	*/
	bool GetIsSkeltal()const { return isSkelton; }

	/*
	@return �J���[�`�F���W��p���邩
	*/
	bool GetIsColorChange()const { return isColorChange; }
	
};

