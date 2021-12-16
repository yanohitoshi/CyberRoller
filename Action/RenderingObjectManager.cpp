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
#include "GraphicsResourceManager.h"

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
	, spriteVerts(nullptr)
	, particleVertex(nullptr)
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


	//undefineTexID = CreateTexture("Assets/sprite/noneTexture.png")->GetTextureID();

	//�@HDRrenderer�̐���
	hdrRenderer = new HDRRenderer(screenWidth, screenHeight,4);
	geometryInstanceManager = new GeometryInstanceManager();
	// �J�����O�̃��[�h�ݒ�
	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	return true;
}

/*
@brief  �I������
*/
void RenderingObjectManager::Shutdown()
{
	// vertex�̌�Еt��
	delete particleVertex;
	delete spriteVerts;
	delete cubeVerts;

	// �R���e�L�X�g��window�̌�Еt��
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/*
@brief  ���[�h�����f�[�^�̉��
*/
void RenderingObjectManager::UnloadData()
{
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
	// sprite�p�r���[�s��̐ݒ�
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj((float)screenWidth, (float)screenHeight);
	Shader* useShader = nullptr;
	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SPRITE);
	useShader->SetActive();
	useShader->SetMatrixUniform("uViewProj", viewProj);
	// ���ׂẴX�v���C�g�̕`��
	for (auto sprite : spriteComponents)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(useShader);
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
		auto iter = spriteComponents.begin();
		for (;
			iter != spriteComponents.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		// ���������ꏊ��iter�̏ꏊ�ɑ}��
		spriteComponents.insert(iter, _spriteComponent);
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
		auto iter = std::find(spriteComponents.begin(), spriteComponents.end(), _spriteComponent);
		spriteComponents.erase(iter);
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
	auto iter = particleComponents.begin();
	for (;
		iter != particleComponents.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	// ���������ꏊ��iter�̏ꏊ�ɑ}��
	particleComponents.insert(iter, _particleComponent);
}

/*
@brief  �X�v���C�g�̍폜
@param	�폜����ParticleObject�N���X�̃|�C���^
*/
void RenderingObjectManager::RemoveParticle(ParticleComponent * _particleComponent)
{
	// �p�[�e�B�N���R���e�i����T���č폜
	auto iter = std::find(particleComponents.begin(), particleComponents.end(), _particleComponent);
	particleComponents.erase(iter);
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
		skeletalMeshComponents.emplace_back(sk);
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
		auto iter = std::find(skeletalMeshComponents.begin(), skeletalMeshComponents.end(), sk);
		skeletalMeshComponents.erase(iter);
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
@brief  �V���h�E�}�b�v�̖{�`��֐�
*/
void RenderingObjectManager::DrawShadowMap()
{

	Shader* useShader = nullptr;

	/* HDR�ƃV���h�E�}�b�v�̏����J�n */
	// HDR���R�[�f�B���O�J�n
	hdrRenderer->HdrRecordBegin();

	// �X�J�C�{�b�N�X�`��
	if (activeSkyBox != nullptr)
	{
		useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SKYBOX);
		useShader->SetActive();
		
		// �Q�[���̋�Ԃɍ��킹�邽�߂̃I�t�Z�b�g�s����Z�b�g
		Matrix4 offset = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
		useShader->SetMatrixUniform("u_offset", offset);

		// Uniform�ɋt�s����Z�b�g
		Matrix4 InvView = view;
		InvView.Invert();
		InvView.Transpose();
		useShader->SetMatrixUniform("u_invView", InvView);
		useShader->SetMatrixUniform("u_projection", projection);
		useShader->SetIntUniform("u_skybox", 0);

		activeSkyBox->Draw(useShader);
	}

	// �����蔻��f�o�b�OBox�̕\��
	PHYSICS->DebugShowBox();

	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::GEOMETRY_INSTANCE);
	//�V���h�E�}�b�vshader���A�N�e�B�u
	useShader->SetActive();
	// ���C�g�̃J�������
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	useShader->SetFloatUniform("uLuminance", 1.0f);

	// �f�B���N�V���i�����C�g
	useShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	useShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	useShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	useShader->SetMatrixUniform("view", view);
	useShader->SetMatrixUniform("projection", projection);

	// �f�v�X�}�b�v���Z�b�g�i���b�V���p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	useShader->SetIntUniform("depthMap", 4);
	useShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);
	geometryInstanceManager->PrepareModelMatrice();
	geometryInstanceManager->Draw(useShader);



	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SHADOW);

	//�V���h�E�}�b�vshader���A�N�e�B�u
	useShader->SetActive();
	// ���C�g�̃J�������
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	useShader->SetFloatUniform("uLuminance", 1.0f);

	// �f�B���N�V���i�����C�g
	useShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	useShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	useShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	useShader->SetMatrixUniform("view", view);
	useShader->SetMatrixUniform("projection", projection);

	// �f�v�X�}�b�v���Z�b�g�i���b�V���p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	useShader->SetIntUniform("depthMap", 4);

	useShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);


	// �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
	// ���ׂẴ��b�V���̕`��
	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(useShader);
		}
	}


	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SKINNED_SHADOW);
	//�V���h�E�}�b�vshader���A�N�e�B�u(skinnend)
	useShader->SetActive();
	// ���C�g�̃J�������
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	// �f�B���N�V���i�����C�g
	useShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	useShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	useShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);
	useShader->SetFloatUniform("uLuminance", 1.0f);
	useShader->SetMatrixUniform("uViewProj", view * projection);
	// �f�v�X�}�b�v���Z�b�g�i�X�L�j���O�p�j
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	useShader->SetIntUniform("depthMap", 4);
	useShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	for (auto sk : skeletalMeshComponents)
	{
		if (sk->GetVisible())
		{
			sk->Draw(useShader);
		}
	}


	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SWITCH);

	useShader->SetActive();
	useShader->SetMatrixUniform("uViewProj", view* projection);
	// ���C�g�̃J�������
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// �A���r�G���g���C�g
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	// �f�B���N�V���i�����C�g
	useShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	useShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	useShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	useShader->SetMatrixUniform("view", view);
	useShader->SetMatrixUniform("projection", projection);

	for (auto mc : colorChangeMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(useShader);
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
	Shader* useShader = nullptr;

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


	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::DEPTH);
	// �f�v�X�}�b�v�Ă��p�V�F�[�_��L�������A�K�v�Ȓl���V�F�[�_�ɃZ�b�g�E�V���h�E���������I�u�W�F�N�g��`�悷��
	// ���b�V�����f���V�F�[�_�[�A�N�e�B�u
	useShader->SetActive();
	useShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	// ���b�V�����f���̕`��
	for (auto mc : meshComponents)
	{
		// �ǈȊO��[�x�}�b�v�ɏ�������
		// ���ǂ̉e��`�悷��ƌ����ڏ㌩�Â炩��������
		Tag checkTag = mc->GetOwner()->GetTag();

		if (mc->GetVisible() && checkTag != Tag::WALL)
		{
			mc->Draw(useShader);
		}
	}

	// ���C�g�p�v���W�F�N�V�����쐬
	lightProjection = Matrix4::CreateOrtho(LightProjectionWhidth, LightProjectionHight, LightProjectionNear, LightProjectionFar);
	// �r���[�s��̍X�V
	lightView = Matrix4::CreateLookAt(LightPos, playerPos, Vector3::UnitX);
	// ���C�g��ԍs����v�Z
	lightSpeceMatrix = lightView * lightProjection;

	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SKINNED_DEPTH);

	// �X�L�j���O���f���V�F�[�_�[�A�N�e�B�u
	useShader->SetActive();
	useShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	// �X�L�j���O���f���̕`��
	for (auto sk : skeletalMeshComponents)
	{
		if (sk->GetVisible())
		{
			sk->Draw(useShader);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

/*
@brief  Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void RenderingObjectManager::DrawParticle()
{
	// particle�̃R���e�i���\�[�g
	std::sort(particleComponents.begin(), particleComponents.end(), std::greater<ParticleComponent*>());

	// particle��0��������X�L�b�v
	if (particleComponents.size() == 0)
	{
		return;
	}

	// �u�����h���[�h������Ԏ擾
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = particleComponents.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// �e�N�X�`��ID������Ԏ擾
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// �r���[�v���W�F�N�V�����s��
	Matrix4 viewProjectionMat;
	viewProjectionMat = view * projection;

	Shader* useShader = nullptr;

	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::PARTICLE);
	// �V�F�[�_�[ON
	useShader->SetActive();
	useShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// �S�Ẵp�[�e�B�N���̃r���{�[�h�s����Z�b�g
	(*itr)->SetBillboardMat(GetBillboardMatrix());


	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// ���ׂẴp�[�e�B�N����`��
	glActiveTexture(GL_TEXTURE0);
	useShader->SetIntUniform("uTexture", 0);

	// �u�����h���[�h�̕ύX
	ChangeBlendMode(blendType);
	// texture�̕ύX
	ChangeTexture(nowTexture);

	// particle��`��
	for (auto particle : particleComponents)
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
				useShader->SetIntUniform("uTexture", 0);
				ChangeBlendMode(blendType);
			}

			// �e�N�X�`���ύX���K�v�Ȃ�ύX����
			nowTexture = particle->GetTextureID();

			if (nowTexture != prevTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				useShader->SetIntUniform("uTexture", 0);
				ChangeTexture(nowTexture);
			}

			// �p�[�e�B�N���`��
			particle->Draw(useShader);

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