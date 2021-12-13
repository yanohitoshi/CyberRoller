#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>    

// �V���O���g���Ȃ̂ŃC���X�^���X��getter��ÓI�̈��define�Œ�`
#define GRAPHICS_RESOURCE GraphicsResourceManager::GetInstance()

// �N���X�̑O���錾
class Mesh;
class MeshComponent;
class SpriteComponent;
class ParticleComponent;
class Texture;
class VertexArray;
class Shader;

/*
enum class �V�F�[�_�[�̎�ނ𔻕ʂ���^�O
*/
enum class ShaderTag
{
    SPRITE,
    SKYBOX,
    SWITCH,
    GEOMETRY_INSTANCE,
    DEPTH,
    SKINNED_DEPTH,
    SHADOW,
    SKINNED_SHADOW,
    PARTICLE,
    DEBUG,
};

class GraphicsResourceManager
{

public:

    /*
    @brief  �C���X�^���X���擾����
    @return AudioManager�N���X�̃C���X�^���X
    */

    static GraphicsResourceManager* GetInstance() { return graphicsResource; }

    /*
    @brief  �C���X�^���X���쐬����
    */
    static void CreateInstance();

    /*
    @brief  �C���X�^���X���폜����
    */
    static void DeleteInstance();

    /*
    @brief  �X�v���C�g�̒ǉ�
    @param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
    */
    void AddSpriteComponent(SpriteComponent* _spriteComponent);

    /*
    @brief �X�v���C�g�̍폜
    @param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
    */
    void RemoveSpriteComponent(SpriteComponent* _spriteComponent);

    /*
    @brief  �p�[�e�B�N���̒ǉ�
    @param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
    */
    void AddParticleComponent(ParticleComponent* _particleComponent);

    /*
    @brief  �X�v���C�g�̍폜
    @param	�폜����ParticleObject�N���X�̃|�C���^
    */
    void RemoveParticleComponent(ParticleComponent* _particleComponent);

    /*
    @brief  ���b�V���R���|�[�l���g�̒ǉ�
    @param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
    */
    void AddMeshComponent(MeshComponent* _meshComponent);

    /*
    @brief  ���b�V���R���|�[�l���g�̍폜
    @param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
    */
    void RemoveMeshComponent(MeshComponent* _meshComponent);

    /*
    @brief	Particle�p���_�f�[�^�̃Z�b�g�֐�
    */
    void SetParticleVertex();

    // �A�N�e�B�u�X�J�C�{�b�N�X
    void SetActiveSkyBox(class CubeMapComponent* in_skyBox) { activeSkyBox = in_skyBox; }
    class CubeMapComponent* GetSkyBox() { return activeSkyBox; }
    class VertexArray* GetCubeMapVerts() { return cubeVerts; }

    /*
    @brief  �V�F�[�_�[�̓ǂݍ���
    @return true : ���� , false : ���s
    */
    bool LoadShaders();

    /*
    @fn �I�������֐�
    @brief ��������Music�ESound�̉���������s��
    */
    void ShutDown();

private:

    /*
    @fn �R���X�g���N�^
    */
    GraphicsResourceManager();

    /*
    @fn �f�X�g���N�^
    @brife �ێ����Ă���S�Ă�Resource���������
    */
    ~GraphicsResourceManager();

    //�����̃C���X�^���X
    static GraphicsResourceManager* graphicsResource;

    // �X�P���g���f�[�^
    std::unordered_map<std::string, class Skeleton*> skeletons;
    // �A�j���[�V�����f�[�^
    std::unordered_map<std::string, class Animation*> anims;

    //�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
    std::unordered_map<std::string, Mesh*> meshes;

    //���b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
    std::vector<MeshComponent*> meshComponents;
    //�J���[�`�F���W�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
    std::vector<MeshComponent*> colorChangeMeshComponents;
    //�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
    std::vector<SpriteComponent*> sprites;
    //�p�[�e�B�N���̃|�C���^
    std::vector<ParticleComponent*> particles;
    //�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
    std::unordered_map<std::string, Texture*>textures;
    // �X�P���g�����b�V���̕`��Ɏg����
    std::vector<class SkeletalMeshComponent*>skeletalMeshes;
    // �F��ς��郁�b�V���̕`��Ɏg����
    std::vector<class ChangeColorMeshComponent*>changeColorMeshes;

    // �g�p����S��ނ̃V�F�[�_�[���i�[����R���e�i
    std::unordered_map<ShaderTag, Shader*> shaders;

    // �X�v���C�g�̒��_�z��
    VertexArray* spriteVerts;

    // �p�[�e�B�N���p���_��`
    VertexArray* particleVertex;

    // �L���[�u���_�z��
    VertexArray* cubeVerts;

    // �t�H���g�}�b�v
    std::unordered_map<std::string, class Font*> fonts;

    // ���ԕ\���p�̃t�H���gtexture
    // ���F
    std::vector<Texture*> timeFontTextures;
    // ���F
    std::vector<Texture*> timeBlackFontTextures;
    // �ԐF
    std::vector<Texture*> timeRedFontTextures;

    // �L���[�u�}�b�v
    class CubeMapComponent* activeSkyBox; // �L����(�`�悷��)�X�J�C�{�b�N�X


    Shader* LoadShader(const std::string& _vertName, const std::string& _fragName);

    /*
    @brief �V�F�[�_���܂Ƃ߂Ă���R���e�i�Ɋi�[����
    @param	_shader �ǉ�����V�F�[�_�[�N���X�̃|�C���^
    @param	_shaderTag ���ƂȂ�V�F�[�_�[�̎�ނ𔻕ʂ���^�O
    */
    void AddShaderMap(Shader* _shader, ShaderTag _shaderTag);

};

