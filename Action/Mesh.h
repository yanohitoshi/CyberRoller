#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include "Math.h"
#include "Collision.h"
#include "Renderer.h"

// �N���X�̑O���錾
class Renderer;
class VertexArray;
class Texture;

/*
@file Mesh.h
@brief ���b�V���f�[�^
*/
class Mesh
{
public:

	/*
	@fn �R���X�g���N�^
	@brief Mesh�N���X�̐���
	*/
    Mesh();
	
	/*
	@fn �f�X�g���N�^
	@brief Mesh�N���X�̍폜
	*/
    ~Mesh();

	/*
	@brief  ���b�V���f�[�^�̓ǂݍ���
	@param	_fileName ���[�h���������b�V���̃t�@�C����
	@param	_renderer Renderer�N���X�̃|�C���^
	@return true : ���� , false : ���s
	*/
    bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@brief  ���[�h�������b�V���f�[�^�̉��
	*/
    void Unload();	

private:

	// �e�N�X�`���X�e�[�W�Ɋ��蓖�Ă�ꂽ�e�N�X�`��
	std::unordered_map<TextureStage, int> stageDefTexture;

    //���̃��b�V���Ɏg���e�N�X�`���̃|�C���^�̉ϒ��R���e�i
    std::vector<Texture*> textures;

	//���̃��b�V���Ɏg�����_�f�[�^
	std::vector<Vector3> verts;

    //���̃��b�V���Ɏg���V�F�[�_�[�̖��O
    std::string shaderName;

	//�N���X�̃|�C���^
    VertexArray* vertexArray;


    //�I�u�W�F�N�g��Ԃł̋��E���̔��a
    float radius;

    //���ʔ��ː����̑傫��
    float specPower;
	
	// ���Ȕ��s���x
	float luminance;

	// AABB�ϐ�
	AABB box;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@brief	VertexArray��getter�֐�
	@return	VertexArray�^�̃|�C���^
	*/
	VertexArray* GetVertexArray() { return vertexArray; }

	/*
	@brief	Texture�N���X��getter�֐�
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(size_t _index);

	/*
	@brief	ShaderName��getter�֐�
	@return ShaderName
	*/
	const std::string& GetShaderName() const { return shaderName; }

	/*
	@brief	���a��getter�֐�
	@return ���a
	*/
	float GetRadius() const { return radius; }

	/*
	@brief	���ʔ��ː�����getter�֐�
	@return ���ʔ��ː���
	*/
	float GetSpecPower() const { return specPower; }

	/*
	@brief	luminance��getter�֐�
	@return luminance
	*/
	float GetLuminace() const { return luminance; }

	/*
	@brief	texture�X�e�[�W���Ƃ�textureID��getter�֐�
	@return texture�X�e�[�W���Ƃ�textureID
	*/
	int GetTextureID(TextureStage stage);

	/*
	@brief	Mesh��AABB��getter�֐�
	@return Mesh��AABB
	*/
	const AABB& GetBox() const { return box; }

	/*
	@brief	���_�f�[�^��getter�֐�
	@return ���_�f�[�^
	*/
	std::vector<Vector3> GetVerts() { return verts; }


};