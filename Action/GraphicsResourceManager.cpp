#include "GraphicsResourceManager.h"
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"

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
	// �V�F�[�_�[�̔j��
	for (auto i : shaders)
	{
		delete i.second;
	}
	shaders.clear();
}

GraphicsResourceManager::GraphicsResourceManager()
{

}

GraphicsResourceManager::~GraphicsResourceManager()
{
	// �����ꂩ��Resource��0�ȏゾ������
	if (shaders.size() > 0)
	{
		// ��Еt��
		ShutDown();
	}
}

void GraphicsResourceManager::AddSpriteComponent(SpriteComponent* _spriteComponent)
{
	//// �w�i���ǂ������擾
	//bool isBackGround = _spriteComponent->GetIsBackGround();
	// �`�揇���擾
	int myDrawOrder = _spriteComponent->GetDrawOrder();

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

void GraphicsResourceManager::RemoveSpriteComponent(SpriteComponent* _spriteComponent)
{
}

void GraphicsResourceManager::AddParticleComponent(ParticleComponent* _particleComponent)
{
}

void GraphicsResourceManager::RemoveParticleComponent(ParticleComponent* _particleComponent)
{
}

void GraphicsResourceManager::AddMeshComponent(MeshComponent* _meshComponent)
{
}

void GraphicsResourceManager::RemoveMeshComponent(MeshComponent* _meshComponent)
{
}

void GraphicsResourceManager::SetParticleVertex()
{
	particleVertex->SetActive();
}


bool GraphicsResourceManager::LoadShaders()
{
	// �i�[�p�V�F�[�_�[
	Shader* shader;
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

	// �f�v�X�}�b�v�Ă��p�V�F�[�_�����[�h(�A�j���[�V�����Ȃ�)
	shader = LoadShader("Shaders/depthmap.vert", "Shaders/depthmap.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::DEPTH);

	// �W�I���g���C���X�^���X��K�p�����`��p�V�F�[�_�����[�h
	shader = LoadShader("Shaders/GeometryInstance.vert", "Shaders/shadowmap.frag");
	// �i�[
	AddShaderMap(shader, ShaderTag::GEOMETRY_INSTANCE);

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
	AddShaderMap(shader, ShaderTag::SKINNED_DEPTH);

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
