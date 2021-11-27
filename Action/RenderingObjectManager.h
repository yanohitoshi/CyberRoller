#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "GameObject.h"

// �V���O���g���Ȃ̂ŃC���X�^���X��getter��ÓI�̈��define�Œ�`
#define RENDERING_OBJECT_MANAGER RenderingObjectManager::GetInstance()

//���s�����p�̍\����
struct DirectionalLight
{
	// ���̕���
	Vector3 direction;
	// �g�U���ːF
	Vector3 diffuseColor;
	// ���ʔ��ːF
	Vector3 specColor;
};

/*
@enum texture�X�e�[�W�̗�
*/
enum class TextureStage
{
	// �f�B�t�[�Y�}�b�v
	DIFFUSE_MAP,
	// �m�[�}���}�b�v
	NORMAL_MAP,
	// �X�y�L�����}�b�v
	SPECULAR_MAP,
	// �G�~�b�V�u�}�b�v
	EMISSIVE_MAP,
	// �V���h�E�}�b�v
	SHADOW_MAP
};

// �N���X�̑O���錾
class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class ChangeColorMeshComponent;
class TileMapSpriteComponent;
class Font;
class HDRRenderer;
class GeometryInstanceManager;

// enum�N���X�̑O�u�錾
enum SceneState;

/*
@file Renderer.h
@brief �`��̐i�s���s���N���X
*/
class RenderingObjectManager
{
public:
	/*
	@brief  �C���X�^���X���擾����
	@return Renderer�N���X�̃C���X�^���X
	*/
	static RenderingObjectManager* GetInstance() { return renderingObjectManager; }

	/*
	@brief  �C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/*
	@brief  �C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/*
	@brief  ����������
	@return true : ���� , false : ���s
	*/
	bool Initialize(int _screenWidth, int _screenHeight, bool _fullScreen);
	/*
	@brief  �I������
	*/
	void Shutdown();

	/*
	@brief  ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	/*
	@brief  �`�揈��
	*/
	void Draw();
	   
	/*
	@brief  �X�v���C�g�̒ǉ�
	@param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@brief �X�v���C�g�̍폜
	@param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@brief  �p�[�e�B�N���̒ǉ�
	@param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@brief  �X�v���C�g�̍폜
	@param	�폜����ParticleObject�N���X�̃|�C���^
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
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

	void SetNowSceneState(SceneState _nowSceneState) { nowSceneState = _nowSceneState; }

private:

	//�R���X�g���N�^�A�f�X�g���N�^�̉B��
	/*
	@brief  �R���X�g���N�^
	*/
	RenderingObjectManager();

	/*
	@brief  �f�X�g���N�^
	*/
	~RenderingObjectManager();

	SceneState nowSceneState;

	//�����̃C���X�^���X
	static RenderingObjectManager* renderingObjectManager;
	SDL_Renderer* sdlRenderer;

	// HDR �����_���[
	HDRRenderer* hdrRenderer;

	// �W�I���g���C���X�^���Xmanager
	GeometryInstanceManager* geometryInstanceManager;

	/*
	@brief  �V�F�[�_�[�̓ǂݍ���
	@return true : ���� , false : ���s
	*/
	bool LoadShaders();
	
	/*
	@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateSpriteVerts();
	
	/*
	@brief  Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateParticleVerts();

	/*
	@brief  �L���[�u�}�b�v(�X�J�C�{�b�N�X�p)���_�z���`
	*/
	void CreateCubeVerts();

	/*
	@brief	���Ԑ����ptexture�̐���
	@param	_value�@�ő�l
	@param _fontSize�@�t�H���g�T�C�Y
	*/
	void CreateTimeFontTexture(int _value,int _fontSize);

	/*
	@brief  �V���h�E�}�b�v�̖{�`��֐�
	*/
	void DrawShadow();

	/*
	@brief  �f�v�X�}�b�v�Ă����ݕ`��
	*/
	void DepthRendering();

	/*
	@brief  �w�i�̕`��
	*/
	void DrawBackGround();

	/*
	@brief  Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void DrawParticle();

	/*
	@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _shader �Z�b�g����Shader�N���X�̃|�C���^
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& view);
	
	/*
	@brief  ��ʑS�̂𕢂����_�̒�`
	@param  vao Vertex Buffer Object
	*/
	void screenVAOSetting(unsigned int& vao);

	/*
	@brief  particle�̃u�����h���[�h��ύX����
	@param  blendType�@�ύX���郂�[�h
	*/
	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM _blendType);
	
	/*
	@brief  texture��ύX����
	@param  changeTextureID�@�ύX����texture��ID
	*/
	void ChangeTexture(int changeTextureID);
	
	/*
	@brief  ���[���h��Ԃ̃J�������W���v�Z
	*/
	Vector3 CalcCameraPos();

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
	//�w�i�摜�p�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> backGroundSprites;

	//�p�[�e�B�N���̃|�C���^
	std::vector<ParticleComponent*> particles;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Texture*>textures;
	// �X�P���g�����b�V���̕`��Ɏg����
	std::vector<class SkeletalMeshComponent*>skeletalMeshes;   
	// �F��ς��郁�b�V���̕`��Ɏg����
	std::vector<class ChangeColorMeshComponent*>changeColorMeshes;

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
	//�N���X�̃|�C���^
	//�X�v���C�g
	Shader* spriteShader;
	VertexArray* spriteVerts;

	// �X�J�C�{�b�N�X�p�V�F�[�_
	Shader* skyboxShader;

	// �X�C�b�`�p�V�F�[�_�[
	Shader* switchShader;
	// �W�I���g���C���X�^���X�p�V�F�[�_�[
	Shader* geometryInstanceShader;
	//�X�L�����b�V��
	Shader*  mSkinnedShader;  

	//shadow�}�b�v�֘A�V�F�[�_�[
	//shadow�p�i���b�V���j
	Shader* depthMapShader;
	Shader* shadowMapShader;

	//shadow�p�i�X�L�����b�V���j
	Shader* skinnedDepthMapShader;
	Shader* skinnedShadowMapShader;

	//�f�o�b�N�p�V�F�[�_�[
	Shader* debugShader;

	//�p�[�e�B�N��
	Shader* particleShader;
	// �p�[�e�B�N���p���_��`
	VertexArray* particleVertex;
	// �L���[�u���_�z��
	VertexArray* cubeVerts;

	//����
	Vector3 ambientLight;
	//���s����
	DirectionalLight dirLight;
	//�E�B���h�E
	SDL_Window* window;
	//�R���e�L�X�g
	SDL_GLContext context;

	// �J�����̎���p
	const float CameraProjectionFov;
	// �J�����v���W�F�N�V�����̋ߋ���
	const float CameraProjectionNear;
	// �J�����v���W�F�N�V�����̉�����
	const float CameraProjectionFar;

	// �V���h�E�}�b�v�̉���
	const unsigned int ShadowWidth;
	// �V���h�E�}�b�v�̏c��
	const unsigned int ShadowHeight;

	// ���C�g�̈ʒu��Z�����v���C���[�̈ʒu���炸�炷�l
	const float ShiftLightPositionZ;
	// ���C�g�̈ʒu��X�����v���C���[�̈ʒu���炸�炷�l
	const float ShiftLightPositionX;

	// ���C�g�v���W�F�N�V�����s�񐶐��p�萔
	// ���C�g�v���W�F�N�V�����̕��̒萔
	const float LightProjectionWhidth;
	// ���C�g�v���W�F�N�V�����̍����̒萔
	const float LightProjectionHight;
	// ���C�g�v���W�F�N�V�����̋ߋ����̒萔
	const float LightProjectionNear;
	// ���C�g�v���W�F�N�V�����̉������̒萔
	const float LightProjectionFar;
	// �������ԗp�t�H���gtexture�̍ő吔�i��肽�������̍ő�l�j
	const int MaxTimeFontTextures;
	// �������ԗp�t�H���g�̃T�C�Y
	const int TimeFontSize;

	//�X�N���[���̉���
	int screenWidth;
	//�X�N���[���̏c��
	int screenHeight;

	// ���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��
	unsigned int undefineTexID;
	//�f�v�X�}�b�v
	unsigned int depthMapFBO;
	// �f�v�X�}�b�vtextureID
	unsigned int depthMap;

	// �v���C���[�̈ʒu�ۑ��p
	Vector3 playerPos;
	// ���C�g�̃|�W�V����
	Vector3 LightPos;
	// ���C�g�̌���
	Vector3 LightDir;
	// �J�����̑O�����x�N�g��
	Vector3 cameraForwardVec;
	// ���C�g�r���[�̃|�W�V����
	Vector3 lightViewPos;

	// ���C�g�̍s��Q
	// �v���W�F�N�V�����A�r���[�A���C�g���
	Matrix4 lightProjection;
	Matrix4 lightView;
	Matrix4 lightSpeceMatrix;

	//�r���[�s��
	Matrix4 view;
	//�ˉe�s��
	Matrix4 projection;
	//�r���{�[�h�s��
	Matrix4 billboardMat;


public://�Q�b�^�[�Z�b�^�[

	/*
	@brief  �e�N�X�`���̎擾
	@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
	@return Texture�N���X�̃|�C���^
	*/
	GeometryInstanceManager* GetGeometryInstanceManager() { return geometryInstanceManager; }

	/*
	@brief  �e�N�X�`���̎擾
	@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(const std::string& _fileName);

	/*
	@brief  �t�H���g�̎擾
	@param	_fileName�@�擾�������t�H���g�̃t�@�C����
	@return Font�N���X�̃|�C���^
	*/
	Font* GetFont(const std::string& _fileName);

	/*
	@brief  �X�P���g�����f���̎擾
	@param _fileName ���f���ւ̃A�h���X
	@return �X�P���g�����f���N���X�̃|�C���^
	*/
	const class Skeleton* GetSkeleton(const char* _fileName);
	
	/*
	@brief  �A�j���[�V�����̎擾
	@param _fileName �A�j���[�V�����ւ̃A�h���X
	@return �X�P���g���A�j���[�V�����N���X�̃|�C���^
	*/
	const class Animation* GetAnimation(const char* _fileName, bool _loop);

	/*
	@brief  ���b�V���̎擾
	@param	_fileName �擾���������b�V���̃t�@�C����
	@return Mesh�N���X�̃|�C���^
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@brief	���s�����̍\���̂��擾����
	@return	DirectionalLight�i���s�����̍\���́j
	*/
	DirectionalLight& GetDirectionalLight() { return dirLight; }

	/*
	@brief	�X�N���[���̉������擾����
	@return	�X�N���[���̉���
	*/
	int GetScreenWidth() const { return screenWidth; }

	/*
	@brief	�X�N���[���̏c�����擾����
	@return	�X�N���[���̏c��
	*/
	int GetScreenHeight() const { return screenHeight; }

	/*
	@brief	View�s���getter
	@return View�s��
	*/
	Matrix4 GetViewMatrix() const { return view; };


	/*
	@brief	Projection�s���getter
	@return Projection�s��
	*/
	Matrix4 GetProjectionMatrix() { return projection; }

	/*
	@brief  SDL_Renderer���擾����
	@return SDL_Renderer�N���X�̃|�C���^
	*/
	SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }
	unsigned int GetUndefineTexID() { return undefineTexID; }

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

	/*
	@brief	�r���[�s���ݒ肷��
	@param	_view �r���[�s��
	*/
	void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/*
	@brief	������ݒ肷��
	@param	_ambient Vector3�i������\���j
	*/
	void SetAmbientLight(Vector3& _ambient) { ambientLight = _ambient; }

	/*
	@brief	�v���C���[�̃|�W�V�������Z�b�g����setter
	@param	�v���C���[�̃|�W�V����
	*/
	void SetPlayerPositon(Vector3 _pos) { playerPos = _pos; }
	/*
	@brief	�J�����̑O���x�N�g�����Z�b�g����setter
	@param	�J�����̑O���x�N�g��
	*/
	void SetCameraForawrd(Vector3 _vec) { cameraForwardVec = _vec; }

};