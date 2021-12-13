#pragma warning(disable:4996)
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "RenderingObjectManager.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include <glew.h>
#include <fstream>
#include <sstream>
#include <document.h>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Skeleton.h"
#include "Animation.h"
#include "SkeletalMeshComponent.h"
#include "CubeMapComponent.h"
#include "Font.h"
#include "GameObject.h"
#include "MainCameraObject.h"
#include "HDRRenderer.h"
#include "GeometryInstanceManager.h"
#include "PhysicsWorld.h"

RenderingObjectManager* RenderingObjectManager::renderingObjectManager = nullptr;

/*
@brief	Particle�p���_�f�[�^�̃Z�b�g�֐�
*/
void RenderingObjectManager::SetParticleVertex()
{
	particleVertex->SetActive();
}

/*
@brief  �R���X�g���N�^
*/
RenderingObjectManager::RenderingObjectManager()
	: hdrRenderer(nullptr)
	, spriteShader(nullptr)
	, spriteVerts(nullptr)
	, particleShader(nullptr)
	, particleVertex(nullptr)
	, depthMapShader(nullptr)
	, switchShader(nullptr)
	, shadowMapShader(nullptr)
	, skinnedDepthMapShader(nullptr)
	, skinnedShadowMapShader(nullptr)
	, view(Matrix4::Identity)
	, projection(Matrix4::Identity)
	, screenWidth(0)
	, screenHeight(0)
	, ambientLight(Vector3::Zero)
	, ShadowWidth (8192)
	, ShadowHeight(8192)
	, CameraProjectionFov(90.0f)
	, CameraProjectionNear(25.0f)
	, CameraProjectionFar(7000.0f)
	, LightProjectionWhidth(20000.0f)
	, LightProjectionHight(20000.0f)
	, LightProjectionNear(1.0f)
	, LightProjectionFar(20000.0f)
	, ShiftLightPositionZ(7000.0f)
	, ShiftLightPositionX(500.0f)
	, MaxTimeFontTextures(501)
	, TimeFontSize(72)
{
}

/*
@brief  �f�X�g���N�^
*/
RenderingObjectManager::~RenderingObjectManager()
{
}

/*
@brief  �C���X�^���X���쐬����
*/
void RenderingObjectManager::CreateInstance()
{
	// ����Ă��Ȃ������琶��
	if (renderingObjectManager == nullptr)
	{
		renderingObjectManager = new RenderingObjectManager();
	}
}

/*
@brief  �C���X�^���X���폜����
*/
void RenderingObjectManager::DeleteInstance()
{
	// �폜����Ă��Ȃ�������폜
	if (renderingObjectManager != nullptr)
	{
		delete renderingObjectManager;
		renderingObjectManager = nullptr;
	}
}

/*
@brief  ����������
@return true : ���� , false : ���s
*/
bool RenderingObjectManager::Initialize(int _screenWidth, int _screenHeight, bool _fullScreen)
{
	// �X�N���[���T�C�Y������
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;

	// OpenGL�̊e������ݒ肷��
	// �R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGL�̎g�p�o�[�W������4.3�Ɏw��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// �_�u���o�b�t�@��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// �n�[�h�E�F�A�A�N�Z�����[�V�������g��
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//�E�B���h�E�̍쐬
	window = SDL_CreateWindow("OpenGL Game", 1, 1,
		static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);

	if (_fullScreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL);
	}

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!sdlRenderer)
	{
		printf("SDLRenderer�̍쐬�Ɏ��s : %s", SDL_GetError());
		return false;
	}

	// OpenGL�̃R���e�L�X�g���쐬
	context = SDL_GL_CreateContext(window);

	// GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// �ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
	glGetError();

	// �V�F�[�_�[�̃��[�h
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	// 3D���f���p�r���[�s��̐ݒ�
	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(CameraProjectionFov),
		(float)screenWidth, (float)screenHeight, CameraProjectionNear, CameraProjectionFar);

	// �V���h�E�p�t���[���o�b�t�@�I�u�W�F�N�g���쐬�E�f�v�X�}�b�v�𐶐����A�V���h�E�o�b�t�@�ɃA�^�b�`
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		ShadowWidth, ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// depthMapFBO�Ƀf�v�X�e�N�X�`�����A�^�b�`����
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//�X�v���C�g�p�̒��_�z����쐬
	CreateSpriteVerts();

	CreateParticleVerts();

	CreateCubeVerts();

	// SDL_ttf�̏�����
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}


	undefineTexID = CreateTexture("Assets/sprite/noneTexture.png")->GetTextureID();

	//�@HDRrenderer�̐���
	hdrRenderer = new HDRRenderer(screenWidth, screenHeight,4);
	geometryInstanceManager = new GeometryInstanceManager();
	// �J�����O�̃��[�h�ݒ�
	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	// �J�E���g�_�E���^�C���ptexture����
	CreateTimeFontTexture(MaxTimeFontTextures, TimeFontSize);

	return true;
}

/*
@brief  �I������
*/
void RenderingObjectManager::Shutdown()
{
	//shader��vertex�̌�Еt��
	delete particleVertex;
	particleShader->Unload();
	delete particleShader;

	delete spriteVerts;

	spriteShader->Unload();
	delete spriteShader;

	switchShader->Unload();
	delete switchShader;

	depthMapShader->Unload();
	delete depthMapShader;

	shadowMapShader->Unload();
	delete shadowMapShader;

	skinnedDepthMapShader->Unload();
	delete skinnedDepthMapShader;

	skinnedShadowMapShader->Unload();
	delete skinnedShadowMapShader;

	//�R���e�L�X�g��window�̌�Еt��
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/*
@brief  ���[�h�����f�[�^�̉��
*/
void RenderingObjectManager::UnloadData()
{
	// ���ׂẴe�N�X�`���̃f�[�^�����
	for (auto i : textures)
	{
		i.second->Unload();
		delete i.second;
	}
	textures.clear();

	// ���ׂẴ��b�V���̃f�[�^�����
	for (auto i : meshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// �X�P���g���̉��
	for (auto s : skeletons)
	{
		delete s.second;
	}
	// �A�j���[�V�����̉��
	for (auto a : anims)
	{
		delete a.second;
	}

	meshes.clear();
	skeletons.clear();
	anims.clear();
}

/*
@brief  �`�揈��
*/
void RenderingObjectManager::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �f�v�X�}�b�v�����_�����O
	BakeDepthMap();

	//�V���h�E�}�b�v�`��
	DrawShadowMap();

	// particle�`��
	DrawParticle();

	// UI�n�X�v���C�g�R���|�[�l���g�̕`��
	// �A���t�@�u�����f�B���O��L���ɂ���
	glEnable(GL_BLEND);
	// �f�v�X�o�b�t�@�@�𖳌��ɂ���
	glDisable(GL_DEPTH_TEST);


	// RGB�����ƃ������̃u�����f�B���O���@��ʁX�ɐݒ�
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB�����ƃA���t�@�����ɕʁX�̍����W����ݒ�
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
	spriteShader->SetActive();
	// sprite�p�r���[�s��̐ݒ�
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj((float)screenWidth, (float)screenHeight);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);
	spriteVerts->SetActive();
	// ���ׂẴX�v���C�g�̕`��
	for (auto sprite : sprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(spriteShader);
		}
	}

	// �o�b�t�@������
	SDL_GL_SwapWindow(window);
}

/*
@brief  �X�v���C�g�̒ǉ�
@param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
*/
void RenderingObjectManager::AddSprite(SpriteComponent* _spriteComponent)
{
	// �w�i���ǂ������擾
	bool isBackGround = _spriteComponent->GetIsBackGround();
	// �`�揇���擾
	int myDrawOrder = _spriteComponent->GetDrawOrder();

	// �w�i����Ȃ�������ʏ�̃R���e�i�Ɋi�[
	if (isBackGround == false)
	{
		// �`�揇�ɉ����Ēǉ�
		// ������X�v���C�g����}������ꏊ�̌���
		// (DrawOrder�����������Ԃɕ`�悷�邽��)
		auto iter = sprites.begin();
		for (;
			iter != sprites.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		// ���������ꏊ��iter�̏ꏊ�ɑ}��
		sprites.insert(iter, _spriteComponent);
	}
}

/*
@brief �X�v���C�g�̍폜
@param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
*/
void RenderingObjectManager::RemoveSprite(SpriteComponent* _spriteComponent)
{
	// �w�i���ǂ������擾
	bool isBackGround = _spriteComponent->GetIsBackGround();

	// �w�i����Ȃ�������
	if (isBackGround == false)
	{
		// �ʏ�R���e�i����T���č폜
		auto iter = std::find(sprites.begin(), sprites.end(), _spriteComponent);
		sprites.erase(iter);
	}

	// �w�i��������
	if (isBackGround == true)
	{
		// �w�i�R���e�i����T���č폜
		auto iter = std::find(backGroundSprites.begin(), backGroundSprites.end(), _spriteComponent);
		backGroundSprites.erase(iter);
	}

}

/*
@brief  �p�[�e�B�N���̒ǉ�
@param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
*/
void RenderingObjectManager::AddParticle(ParticleComponent * _particleComponent)
{
	// �`�揇���擾
	int myDrawOrder = _particleComponent->GetDrawOrder();
	// �`�揇�ɉ����Ēǉ�
	// ������p�[�e�B�N������}������ꏊ�̌���
	// (DrawOrder�����������Ԃɕ`�悷�邽��)
	auto iter = particles.begin();
	for (;
		iter != particles.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	// ���������ꏊ��iter�̏ꏊ�ɑ}��
	particles.insert(iter, _particleComponent);
}

/*
@brief  �X�v���C�g�̍폜
@param	�폜����ParticleObject�N���X�̃|�C���^
*/
void RenderingObjectManager::RemoveParticle(ParticleComponent * _particleComponent)
{
	// �p�[�e�B�N���R���e�i����T���č폜
	auto iter = std::find(particles.begin(), particles.end(), _particleComponent);
	particles.erase(iter);
}

/*
@brief  ���b�V���R���|�[�l���g�̒ǉ�
@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
*/
void RenderingObjectManager::AddMeshComponent(MeshComponent* _meshComponent)
{
	//���b�V���f�[�^�ɃX�P���g���f�[�^�������
	if (_meshComponent->GetIsSkeltal())
	{
		// �X�L�j���O���f���Ƃ��Đ���
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		skeletalMeshes.emplace_back(sk);
	}
	else if(_meshComponent->GetIsColorChange() == true) // �r���ŐF�̕ύX�������Ȃ����b�V����������
	{
		// �F�ύX�K�p�V�F�[�_�[��p���郂�f���Ƃ��Ċi�[
		colorChangeMeshComponents.emplace_back(_meshComponent);
	}
	else
	{
		// �ʏ탂�f���R���e�i�Ɋi�[
		meshComponents.emplace_back(_meshComponent);
	}
}


/*
@brief  ���b�V���R���|�[�l���g�̍폜
@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
*/
void RenderingObjectManager::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	//���b�V���f�[�^�ɃX�P���g���f�[�^�������
	if (_meshComponent->GetIsSkeltal())
	{
		// �X�L�j���O���f���R���e�i����T���č폜
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(skeletalMeshes.begin(), skeletalMeshes.end(), sk);
		skeletalMeshes.erase(iter);
	}
	else if (_meshComponent->GetIsColorChange()) // �r���ŐF�̕ύX�������Ȃ����b�V����������
	{
		// �F�ύX�K�p�R���e�i����폜
		auto iter = std::find(colorChangeMeshComponents.begin(), colorChangeMeshComponents.end(), _meshComponent);
		colorChangeMeshComponents.erase(iter);
	}
	else
	{
		// �ʏ�R���e�i����폜
		auto iter = std::find(meshComponents.begin(), meshComponents.end(), _meshComponent);
		meshComponents.erase(iter);
	}
}

/*
@param _fileName ���f���ւ̃A�h���X
@return �X�P���g�����f���̎擾
*/
const Skeleton * RenderingObjectManager::CreateSkeleton(const char * _fileName)
{
	//���łɍ쐬����ĂȂ������ׂ�
	std::string file(_fileName);
	auto iter = skeletons.find(file);
	if (iter != skeletons.end())
	{
		return iter->second;
	}
	else 	//�쐬�ς݂łȂ��ꍇ�A�V�����X�P���g�����쐬
	{
		Skeleton* sk = new Skeleton();
		if (sk->Load(file))
		{
			skeletons.emplace(file, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

/*
@param _fileName �A�j���[�V�����ւ̃A�h���X
@return �X�P���g���A�j���[�V�����̎擾
*/
const Animation * RenderingObjectManager::CreateAnimation(const char * _fileName, bool _loop)
{
	//���łɍ쐬����ĂȂ������ׂ�
	auto iter = anims.find(_fileName);
	if (iter != anims.end())
	{
		return iter->second;
	}
	else 	//�쐬�ς݂łȂ��ꍇ�A�V�����A�j���[�V�������쐬
	{
		Animation* anim = new Animation();
		if (anim->Load(_fileName,_loop))
		{
			anims.emplace(_fileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

/*
@brief  �e�N�X�`���̎擾
@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
@return Texture�N���X�̃|�C���^
*/
Texture* RenderingObjectManager::CreateTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = textures.find(_fileName);
	if (itr != textures.end())
	{
		texture = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
		{
			textures.emplace(_fileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

/*
@brief  �t�H���g�̎擾
@param	_fileName�@�擾�������t�H���g�̃t�@�C����
@return Font�N���X�̃|�C���^
*/
Font* RenderingObjectManager::CreateFont(const std::string& _fileName)
{
	Font* font = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = fonts.find(_fileName);
	if (itr != fonts.end())
	{
		font = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����t�H���g���쐬
	else
	{
		font = new Font();
		if (font->Load(_fileName))
		{
			fonts.emplace(_fileName, font);
		}
		else
		{
			delete font;
			font = nullptr;
		}
	}

	return font;
}

/*
@brief  ���b�V���̎擾
@param	_fileName �擾���������b�V���̃t�@�C����
@return Mesh�N���X�̃|�C���^
*/
Mesh* RenderingObjectManager::CreateMesh(const std::string &_fileName)
{
	Mesh* m = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto iter = meshes.find(_fileName);
	if (iter != meshes.end())
	{
		m = iter->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�������b�V�����쐬
	else
	{
		m = new Mesh();
		if (m->Load(_fileName, this))
		{
			meshes.emplace(_fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

/*
@brief  �V�F�[�_�[�̓ǂݍ���
@return true : ���� , false : ���s
*/
bool RenderingObjectManager::LoadShaders()
{
	// �X�v���C�g�V�F�[�_�[�̍쐬
	spriteShader = new Shader();
	if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	// switch�p�V�F�[�_�[�̍쐬(�F�ύX�\�V�F�[�_�[)
	switchShader = new Shader();
	if (!switchShader->Load("Shaders/shadowmap.vert", "Shaders/switch.frag"))
	{
		return false;
	}

	skyboxShader = new Shader();
	if (!skyboxShader->Load("Shaders/gBuffer_SkyBox.vert", "Shaders/gBuffer_SkyBox.frag"))
	{
		return false;
	}

	//particle�V�F�[�_�[
	particleShader = new Shader();
	if (!particleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	// �f�v�X�}�b�v�Ă��p�V�F�[�_(�A�j���[�V�����Ȃ�)
	depthMapShader = new Shader();
	if (!depthMapShader->Load("Shaders/depthmap.vert", "Shaders/depthmap.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	// �W�I���g���C���X�^���X��K�p�����`��p�V�F�[�_�쐬
	geometryInstanceShader = new Shader();
	if (!geometryInstanceShader->Load("Shaders/GeometryInstance.vert", "Shaders/shadowmap.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	// �V���h�E��K�p�����`��p�V�F�[�_�쐬(�A�j���[�V�����Ȃ�)
	shadowMapShader = new Shader();
	if (!shadowMapShader->Load("Shaders/shadowmap.vert", "Shaders/shadowmap.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	// �f�v�X�}�b�v�Ă��p�V�F�[�_ (�A�j���[�V��������)
	skinnedDepthMapShader = new Shader();
	if (!skinnedDepthMapShader->Load("Shaders/SkinnedDepth.vert", "Shaders/depthmap.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��sdepth\n");
	}
	// �V���h�E��K�p�����`��p�V�F�[�_�쐬 (�A�j���[�V��������)
	skinnedShadowMapShader = new Shader();
	if (!skinnedShadowMapShader->Load("Shaders/SkinnedShadow.vert", "Shaders/SkinnedShadow.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��sshadow\n");
	}

	return true;
}

/*
@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void RenderingObjectManager::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // ����
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // �E��
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // �E��
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // ����
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	spriteVerts = new VertexArray(vertices, 4, indices, 6);
}

/*
@brief  Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void RenderingObjectManager::CreateParticleVerts()
{
	float vertices[] = {
		-0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		 0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		 0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 2, 1,
		2, 0, 3
	};
	particleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

/*
@brief  �L���[�u�}�b�v(�X�J�C�{�b�N�X�p)���_�z���`
*/
void RenderingObjectManager::CreateCubeVerts()
{
	cubeVerts = new VertexArray();
	cubeVerts->CreateCubeVerts();
}

/*
@brief	���Ԑ����ptexture�̐���
@param	_value�@�ő�l
@param _fontSize�@�t�H���g�T�C�Y
*/
void RenderingObjectManager::CreateTimeFontTexture(int _value, int _fontSize)
{
	// �t�H���g�̐���
	Font* font = CreateFont("Assets/Config/Fonts/impact.ttf");
	// �i�[����ϒ��z������T�C�Y
	timeFontTextures.resize(_value);
	timeBlackFontTextures.resize(_value);
	timeRedFontTextures.resize(_value);

	// �ő�l��p���ăt�H���g�̐F���Ƃɂ��̖���texture�𐶐�
	// ���F
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeFontTextures[i] = font->RenderText(str,Color::White, _fontSize);
	}

	// ���F�i�o�b�N�t�H���g�p�i�����̉e�j�j
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeBlackFontTextures[i] = font->RenderText(str, Color::Black, _fontSize);
	}

	// �ԐF
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeRedFontTextures[i] = font->RenderText(str, Color::Red, _fontSize);
	}
}

/*
@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
@param	�J�E���g�_�E���^�C��
@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
*/
Texture* RenderingObjectManager::GetTimeTexture(int _time)
{
	return timeFontTextures[_time + 1];
}

/*
@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
@param	�J�E���g�_�E���^�C��
@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
*/
Texture* RenderingObjectManager::GetTimeBlackTexture(int _time)
{
	return timeBlackFontTextures[_time + 1];
}

/*
@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i�ԁj
@param	�J�E���g�_�E���^�C��
@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
*/
Texture* RenderingObjectManager::GetTimeRedTexture(int _time)
{
	return timeRedFontTextures[_time + 1];
}

/*
@brief  �V���h�E�}�b�v�̖{�`��֐�
*/
void RenderingObjectManager::DrawShadowMap()
{

	/* HDR�ƃV���h�E�}�b�v�̏����J�n */
	// HDR���R�[�f�B���O�J�n
	hdrRenderer->HdrRecordBegin();

	// �X�J�C�{�b�N�X�`��
	if (activeSkyBox != nullptr)
	{
		skyboxShader->SetActive();
		
		// �Q�[���̋�Ԃɍ��킹�邽�߂̃I�t�Z�b�g�s����Z�b�g
		Matrix4 offset = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
		skyboxShader->SetMatrixUniform("u_offset", offset);

		// Uniform�ɋt�s����Z�b�g
		Matrix4 InvView = view;
		InvView.Invert();
		InvView.Transpose();
		skyboxShader->SetMatrixUniform("u_invView", InvView);
		skyboxShader->SetMatrixUniform("u_projection", projection);
		skyboxShader->SetIntUniform("u_skybox", 0);

		activeSkyBox->Draw(skyboxShader);
	}

	// �����蔻��f�o�b�OBox�̕\��
	PHYSICS->DebugShowBox();

	//�V���h�E�}�b�vshader���A�N�e�B�u
	geometryInstanceShader->SetActive();
	// ���C�g�̃J�������
	geometryInstanceShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	geometryInstanceShader->SetVectorUniform("uAmbientLight", ambientLight);
	geometryInstanceShader->SetFloatUniform("uLuminance", 1.0f);

	// �f�B���N�V���i�����C�g
	geometryInstanceShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	geometryInstanceShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	geometryInstanceShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	geometryInstanceShader->SetMatrixUniform("view", view);
	geometryInstanceShader->SetMatrixUniform("projection", projection);

	// �f�v�X�}�b�v���Z�b�g�i���b�V���p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	geometryInstanceShader->SetIntUniform("depthMap", 4);
	geometryInstanceShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);
	geometryInstanceManager->PrepareModelMatrice();
	geometryInstanceManager->Draw(geometryInstanceShader);


	//�V���h�E�}�b�vshader���A�N�e�B�u
	shadowMapShader->SetActive();
	// ���C�g�̃J�������
	shadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	shadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	shadowMapShader->SetFloatUniform("uLuminance", 1.0f);

	// �f�B���N�V���i�����C�g
	shadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	shadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	shadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	shadowMapShader->SetMatrixUniform("view", view);
	shadowMapShader->SetMatrixUniform("projection", projection);

	// �f�v�X�}�b�v���Z�b�g�i���b�V���p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	shadowMapShader->SetIntUniform("depthMap", 4);

	shadowMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);


	// �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
	// ���ׂẴ��b�V���̕`��
	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(shadowMapShader);
		}
	}

	//�V���h�E�}�b�vshader���A�N�e�B�u(skinnend)
	skinnedShadowMapShader->SetActive();
	// ���C�g�̃J�������
	skinnedShadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	skinnedShadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	// �f�B���N�V���i�����C�g
	skinnedShadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	skinnedShadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	skinnedShadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);
	skinnedShadowMapShader->SetFloatUniform("uLuminance", 1.0f);
	skinnedShadowMapShader->SetMatrixUniform("uViewProj", view * projection);
	// �f�v�X�}�b�v���Z�b�g�i�X�L�j���O�p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	skinnedShadowMapShader->SetIntUniform("depthMap", 4);
	skinnedShadowMapShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	for (auto sk : skeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(skinnedShadowMapShader);
		}
	}

	switchShader->SetActive();
	switchShader->SetMatrixUniform("uViewProj", view* projection);
	// ���C�g�̃J�������
	switchShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	switchShader->SetVectorUniform("uAmbientLight", ambientLight);
	// �f�B���N�V���i�����C�g
	switchShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	switchShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	switchShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	switchShader->SetMatrixUniform("view", view);
	switchShader->SetMatrixUniform("projection", projection);

	for (auto mc : colorChangeMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(switchShader);
		}
	}

	// HDR���R�[�f�C���O�I��
	hdrRenderer->HdrRecordEnd();

	/* HDR Bloom �̍쐬�ƍ��� */
	// �K�E�X�ڂ����̐���
	hdrRenderer->HiBrightBlurCreate();
	// �K�E�X�ڂ��������摜��HDR���ŏI����
	hdrRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBuffer�Ƀ����_�����O�����Ƃ���Depth�����X�N���[���ɃR�s�[
	hdrRenderer->CopyDepthToScreen();

}

/*
@brief  �f�v�X�}�b�v�Ă����ݕ`��
*/
void RenderingObjectManager::BakeDepthMap()
{
	// �v���C���[�̃|�W�V�������Q�Ƃ��ă��C�g��Ԃ��쐬����ۂ̃|�W�V�������v�Z
	LightPos = Vector3(playerPos.x , playerPos.y , playerPos.z + ShiftLightPositionZ);

	// �f�B���N�V���i�����C�g���烉�C�g�̕������擾
	LightDir = dirLight.direction;
	// ���K��
	LightDir.Normalize();
	// ���C�g�p�v���W�F�N�V�����쐬
	lightProjection = Matrix4::CreateOrtho(LightProjectionWhidth, LightProjectionHight, LightProjectionNear, LightProjectionFar);
	// �r���[�s��̍X�V
	lightView = Matrix4::CreateLookAt(LightPos, Vector3(playerPos.x - 10.0f, playerPos.y - 10.0f, playerPos.z), Vector3::UnitX);
	// ���C�g��ԍs����v�Z
	lightSpeceMatrix = lightView * lightProjection;

	// �r���[�|�[�g��[�x�}�b�v�T�C�Y�ɐݒ肷��
	glViewport(0, 0, ShadowWidth, ShadowHeight);
	// �V���h�E�t���[���o�b�t�@���o�C���h
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

	glClear(GL_DEPTH_BUFFER_BIT);

	// �f�v�X�}�b�v�Ă��p�V�F�[�_��L�������A�K�v�Ȓl���V�F�[�_�ɃZ�b�g�E�V���h�E���������I�u�W�F�N�g��`�悷��
	// ���b�V�����f���V�F�[�_�[�A�N�e�B�u
	depthMapShader->SetActive();
	depthMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	// ���b�V�����f���̕`��
	for (auto mc : meshComponents)
	{
		// �ǈȊO��[�x�}�b�v�ɏ�������
		// ���ǂ̉e��`�悷��ƌ����ڏ㌩�Â炩��������
		Tag checkTag = mc->GetOwner()->GetTag();

		if (mc->GetVisible() && checkTag != Tag::WALL)
		{
			mc->Draw(depthMapShader);
		}
	}

	// ���C�g�p�v���W�F�N�V�����쐬
	lightProjection = Matrix4::CreateOrtho(LightProjectionWhidth, LightProjectionHight, LightProjectionNear, LightProjectionFar);
	// �r���[�s��̍X�V
	lightView = Matrix4::CreateLookAt(LightPos, playerPos, Vector3::UnitX);
	// ���C�g��ԍs����v�Z
	lightSpeceMatrix = lightView * lightProjection;

	// �X�L�j���O���f���V�F�[�_�[�A�N�e�B�u
	skinnedDepthMapShader->SetActive();
	skinnedDepthMapShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	// �X�L�j���O���f���̕`��
	for (auto sk : skeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(skinnedDepthMapShader);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

}

/*
@brief  �w�i�̕`��
*/
void RenderingObjectManager::DrawBackGround()
{
	// �A���t�@�u�����f�B���O��L���ɂ���
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	// RGB�����ƃ������̃u�����f�B���O���@��ʁX�ɐݒ�
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB�����ƃA���t�@�����ɕʁX�̍����W����ݒ�
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// �X�v���C�g�R���|�[�l���g�̕`��(�w�i)
	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
	spriteShader->SetActive();
	spriteVerts->SetActive();
	glActiveTexture(GL_TEXTURE0);
	spriteShader->SetIntUniform("uTexture", 0);

	// ���ׂẴX�v���C�g�̕`��
	for (auto sprite : backGroundSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(spriteShader);
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

/*
@brief  Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void RenderingObjectManager::DrawParticle()
{
	// particle�̃R���e�i���\�[�g
	std::sort(particles.begin(), particles.end(), std::greater<ParticleComponent*>());

	// particle��0��������X�L�b�v
	if (particles.size() == 0)
	{
		return;
	}

	// �u�����h���[�h������Ԏ擾
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = particles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// �e�N�X�`��ID������Ԏ擾
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// �r���[�v���W�F�N�V�����s��
	Matrix4 viewProjectionMat;
	viewProjectionMat = view * projection;

	// �V�F�[�_�[ON
	particleShader->SetActive();
	particleShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// �S�Ẵp�[�e�B�N���̃r���{�[�h�s����Z�b�g
	(*itr)->SetBillboardMat(GetBillboardMatrix());


	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// ���ׂẴp�[�e�B�N����`��
	glActiveTexture(GL_TEXTURE0);
	particleShader->SetIntUniform("uTexture", 0);

	// �u�����h���[�h�̕ύX
	ChangeBlendMode(blendType);
	// texture�̕ύX
	ChangeTexture(nowTexture);

	// particle��`��
	for (auto particle : particles)
	{
		// �`�悷���Ԃ�������
		if (particle->GetVisible())
		{
			//�u�����h���[�h�ύX���K�v�Ȃ�ύX����
			blendType = particle->GetBlendType();
			blendType = particle->GetBlendType();

			if (blendType != prevType)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeBlendMode(blendType);
			}

			// �e�N�X�`���ύX���K�v�Ȃ�ύX����
			nowTexture = particle->GetTextureID();

			if (nowTexture != prevTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeTexture(nowTexture);
			}

			// �p�[�e�B�N���`��
			particle->Draw(particleShader);

			// �O��`���ԂƂ��ĕۑ�
			prevType = blendType;
			prevTexture = nowTexture;
		}
	}

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

/*
@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
@param _shader �Z�b�g����Shader�N���X�̃|�C���^
*/
void RenderingObjectManager::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// �r���[�s����t�s��ɂ���
	Matrix4 invView = _view;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// �����̐ݒ�
	_shader->SetVectorUniform("uAmbientLight", ambientLight);
	// ���s�����̐ݒ�
	_shader->SetVectorUniform("uDirLight.mDirection",
		dirLight.direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		dirLight.diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		dirLight.specColor);
}

/*
@brief  particle�̃u�����h���[�h��ύX����
@param  blendType�@�ύX���郂�[�h
*/
void RenderingObjectManager::ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM _blendType)
{
	// PARTICLE_BLEND_ENUM�̃^�C�v���Q��
	switch (_blendType)
	{
	case ParticleComponent::PARTICLE_BLEND_ENUM_ADD:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //���Z����
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // �A���t�@�u�����h
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //��Z����
		break;
	default:
		break;
	}
}

/*
@brief  texture��ύX����
@param  changeTextureID�@�ύX����texture��ID
*/
void RenderingObjectManager::ChangeTexture(int changeTextureID)
{
	// textureID���o�C���h
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

/*
@brief  ���[���h��Ԃ̃J�������W���v�Z
*/
Vector3 RenderingObjectManager::CalcCameraPos()
{
	// �r���[�s���胏�[���h�ł̃J�����ʒu�Z�o
	Matrix4 transMat = view;

	// �r���[�s��̈ړ������������
	Vector3 v;
	v.x = -1.0f * view.mat[3][0];
	v.y = -1.0f * view.mat[3][1];
	v.z = -1.0f * view.mat[3][2];

	//�ړ���������菜�������Ɠ]�u���āA��]�����̋t�ϊ������
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}

/*
@brief  ��ʑS�̂𕢂����_�̒�`
@param  vao Vertex Buffer Object
*/
void RenderingObjectManager::screenVAOSetting(unsigned int& vao)
{
	unsigned int vbo;
	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup plane VAO
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}