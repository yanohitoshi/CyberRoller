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
class Font;

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
    @brief  �e�N�X�`���̎擾
    @param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
    @return Texture�N���X�̃|�C���^
    */
    Texture* CreateTexture(const std::string& _fileName);

    /*
    @brief  �t�H���g�̎擾
    @param	_fileName�@�擾�������t�H���g�̃t�@�C����
    @return Font�N���X�̃|�C���^
    */
    Font* CreateFont(const std::string& _fileName);

    /*
    @brief  �X�P���g�����f���̎擾
    @param _fileName ���f���ւ̃A�h���X
    @return �X�P���g�����f���N���X�̃|�C���^
    */
    const class Skeleton* CreateSkeleton(const char* _fileName);

    /*
    @brief  �A�j���[�V�����̎擾
    @param _fileName �A�j���[�V�����ւ̃A�h���X
    @return �X�P���g���A�j���[�V�����N���X�̃|�C���^
    */
    const class Animation* CreateAnimation(const char* _fileName, bool _loop);

    /*
    @brief  ���b�V���̎擾
    @param	_fileName �擾���������b�V���̃t�@�C����
    @return Mesh�N���X�̃|�C���^
    */
    Mesh* CreateMesh(const std::string& _fileName);

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

    /*
    @brief	���Ԑ����ptexture�̐���
    @param	_value�@�ő�l
    @param _fontSize�@�t�H���g�T�C�Y
    */
    void CreateTimeFontTexture(int _value, int _fontSize);


    //�����̃C���X�^���X
    static GraphicsResourceManager* graphicsResource;

    // �X�P���g���f�[�^
    std::unordered_map<std::string, class Skeleton*> skeletons;
    // �A�j���[�V�����f�[�^
    std::unordered_map<std::string, class Animation*> anims;

    //�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
    std::unordered_map<std::string, Mesh*> meshes;

    //�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
    std::unordered_map<std::string, Texture*>textures;

    // �g�p����S��ނ̃V�F�[�_�[���i�[����R���e�i
    std::unordered_map<ShaderTag, Shader*> shaders;

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

    // �������ԗp�t�H���gtexture�̍ő吔�i��肽�������̍ő�l�j
    const int MaxTimeFontTextures;
    // �������ԗp�t�H���g�̃T�C�Y
    const int TimeFontSize;

public:

    /*
    @brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
    @param	�J�E���g�_�E���^�C��
    @return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
    */
    Texture* GetTimeTexture(int _time);

    /*
    @brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
    @param	�J�E���g�_�E���^�C��
    @return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
    */
    Texture* GetTimeBlackTexture(int _time);

    /*
    @brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i�ԁj
    @param	�J�E���g�_�E���^�C��
    @return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
    */
    Texture* GetTimeRedTexture(int _time);

    Shader* FindUseShader(ShaderTag _shaderTag);

};

