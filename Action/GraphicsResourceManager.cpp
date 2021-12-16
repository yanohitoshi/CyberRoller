#include "GraphicsResourceManager.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Font.h"
#include "Texture.h"
#include "Mesh.h"
#include "Skeleton.h"
#include "Animation.h"
#include "SpriteComponent.h"
#include "ParticleComponent.h"
#include "MeshComponent.h"
#include "SkeletalMeshComponent.h"
#include <string>

GraphicsResourceManager* GraphicsResourceManager::graphicsResource = nullptr;

void GraphicsResourceManager::CreateInstance()
{
	// ����Ă��Ȃ������琶��
	if (graphicsResource == nullptr)
	{
		graphicsResource = new GraphicsResourceManager();
	}
}

void GraphicsResourceManager::DeleteInstance()
{
	// �폜����Ă��Ȃ�������폜
	if (graphicsResource != nullptr)
	{
		delete graphicsResource;
		graphicsResource = nullptr;
	}
}

void GraphicsResourceManager::ShutDown()
{
	// ���ׂẴe�N�X�`���̃f�[�^�����
	for (auto texture : textures)
	{
		texture.second->Unload();
		delete texture.second;
	}

	textures.clear();

	// ���ׂẴ��b�V���̃f�[�^�����
	for (auto meshe : meshes)
	{
		meshe.second->Unload();
		delete meshe.second;
	}
	meshes.clear();

	// �X�P���g���̉��
	for (auto skeleton : skeletons)
	{
		delete skeleton.second;
	}
	skeletons.clear();

	// �A�j���[�V�����̉��
	for (auto anim : anims)
	{
		delete anim.second;
	}
	anims.clear();

	// �V�F�[�_�[�̔j��
	for (auto shader : shaders)
	{
		shader.second->Unload();
		delete shader.second;
	}
	shaders.clear();
}

GraphicsResourceManager::GraphicsResourceManager()
	: MaxTimeFontTextures(501)
	, TimeFontSize(72)
{

	// �V�F�[�_�[�̃��[�h
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		//return false;
	}

	// �J�E���g�_�E���^�C���ptexture����
	CreateTimeFontTexture(MaxTimeFontTextures, TimeFontSize);
}

GraphicsResourceManager::~GraphicsResourceManager()
{
	// ��Еt��
	ShutDown();
}

void GraphicsResourceManager::CreateTimeFontTexture(int _value, int _fontSize)
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
		timeFontTextures[i] = font->RenderText(str, Color::White, _fontSize);
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

Texture* GraphicsResourceManager::CreateTexture(const std::string& _fileName)
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

Font* GraphicsResourceManager::CreateFont(const std::string& _fileName)
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

const Skeleton* GraphicsResourceManager::CreateSkeleton(const char* _fileName)
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

const Animation* GraphicsResourceManager::CreateAnimation(const char* _fileName, bool _loop)
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
		if (anim->Load(_fileName, _loop))
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


Mesh* GraphicsResourceManager::CreateMesh(const std::string& _fileName)
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

bool GraphicsResourceManager::LoadShaders()
{
	// �i�[�p�V�F�[�_�[
	Shader* shader = nullptr;
	shader = LoadShader("Shaders/Sprite.vert", "Shaders/Sprite.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::SPRITE);

	// switch�p�V�F�[�_�[�̍쐬(�F�ύX�\�V�F�[�_�[)
	shader = LoadShader("Shaders/shadowmap.vert", "Shaders/switch.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::SWITCH);

	// �X�J�C�{�b�N�X�p�V�F�[�_�[�����[�h
	shader = LoadShader("Shaders/gBuffer_SkyBox.vert", "Shaders/gBuffer_SkyBox.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::SKYBOX);

	//particle�V�F�[�_�[�����[�h
	shader = LoadShader("Shaders/Phong.vert", "Shaders/Particle.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::PARTICLE);

	// �W�I���g���C���X�^���X��K�p�����`��p�V�F�[�_�����[�h
	shader = LoadShader("Shaders/GeometryInstance.vert", "Shaders/shadowmap.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::GEOMETRY_INSTANCE);

	// �f�v�X�}�b�v�Ă��p�V�F�[�_�����[�h(�A�j���[�V�����Ȃ�)
	shader = LoadShader("Shaders/depthmap.vert", "Shaders/depthmap.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::DEPTH);

	// �V���h�E��K�p�����`��p�V�F�[�_�����[�h(�A�j���[�V�����Ȃ�)
	shader = LoadShader("Shaders/shadowmap.vert", "Shaders/shadowmap.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::SHADOW);

	// �f�v�X�}�b�v�Ă��p�V�F�[�_�����[�h (�A�j���[�V��������)
	shader = LoadShader("Shaders/SkinnedDepth.vert", "Shaders/depthmap.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::SKINNED_DEPTH);

	// �V���h�E��K�p�����`��p�V�F�[�_�����[�h(�A�j���[�V��������)
	shader = LoadShader("Shaders/SkinnedShadow.vert", "Shaders/SkinnedShadow.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::SKINNED_SHADOW);

	return true;
}

Shader* GraphicsResourceManager::LoadShader(const std::string& _vertName, const std::string& _fragName)
{
	// �����p�V�F�[�_�[
	Shader* shader;
	// �X�v���C�g�V�F�[�_�[�̍쐬
	shader = new Shader();
	if (!shader->Load(_vertName, _fragName))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
		return nullptr;
	}

	return shader;
}

void GraphicsResourceManager::AddShaderMap(Shader* _shader, ShaderTag _shaderTag)
{
	//�}�b�v�̒��ɒǉ�����V�F�[�_�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = shaders.find(_shaderTag);

	//����Ƃ�
	if (stateMaps != shaders.end())
	{
		return;
	}
	else //�Ȃ��Ƃ�
	{
		shaders[_shaderTag] = _shader;
	}
}


/*
@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
@param	�J�E���g�_�E���^�C��
@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
*/
Texture* GraphicsResourceManager::GetTimeTexture(int _time)
{
	return timeFontTextures[_time + 1];
}

/*
@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
@param	�J�E���g�_�E���^�C��
@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
*/
Texture* GraphicsResourceManager::GetTimeBlackTexture(int _time)
{
	return timeBlackFontTextures[_time + 1];
}

/*
@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i�ԁj
@param	�J�E���g�_�E���^�C��
@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
*/
Texture* GraphicsResourceManager::GetTimeRedTexture(int _time)
{
	return timeRedFontTextures[_time + 1];
}

Shader* GraphicsResourceManager::FindUseShader(ShaderTag _shaderTag)
{
	//�}�b�v�̒��ɒǉ�����V�F�[�_�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = shaders.find(_shaderTag);
	//����Ƃ�
	if (stateMaps != shaders.end())
	{
		// �g�p����V�F�[�_�[��Ԃ�
		return shaders[_shaderTag];
	}
	else //�Ȃ��Ƃ�
	{
		return nullptr;
	}
}
