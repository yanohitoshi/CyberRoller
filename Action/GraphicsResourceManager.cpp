#include "GraphicsResourceManager.h"
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"

GraphicsResourceManager* GraphicsResourceManager::graphicsResource = nullptr;

void GraphicsResourceManager::CreateInstance()
{
	// 作られていなかったら生成
	if (graphicsResource == nullptr)
	{
		graphicsResource = new GraphicsResourceManager();
	}
}

void GraphicsResourceManager::DeleteInstance()
{
	// 削除されていなかったら削除
	if (graphicsResource != nullptr)
	{
		delete graphicsResource;
		graphicsResource = nullptr;
	}
}

void GraphicsResourceManager::ShutDown()
{
	// シェーダーの破棄
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
	// いずれかのResourceが0以上だったら
	if (shaders.size() > 0)
	{
		// 後片付け
		ShutDown();
	}
}

void GraphicsResourceManager::AddSpriteComponent(SpriteComponent* _spriteComponent)
{
	//// 背景かどうかを取得
	//bool isBackGround = _spriteComponent->GetIsBackGround();
	// 描画順を取得
	int myDrawOrder = _spriteComponent->GetDrawOrder();

	// 描画順に沿って追加
	// 今あるスプライトから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
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

	// 検索した場所のiterの場所に挿入
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
	// 格納用シェーダー
	Shader* shader;
	shader = LoadShader("Shaders/Sprite.vert", "Shaders/Sprite.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::SPRITE);

	// switch用シェーダーの作成(色変更可能シェーダー)
	shader = LoadShader("Shaders/shadowmap.vert", "Shaders/switch.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::SWITCH);

	// スカイボックス用シェーダーをロード
	shader = LoadShader("Shaders/gBuffer_SkyBox.vert", "Shaders/gBuffer_SkyBox.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::SKYBOX);

	//particleシェーダーをロード
	shader = LoadShader("Shaders/Phong.vert", "Shaders/Particle.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::PARTICLE);

	// デプスマップ焼き用シェーダをロード(アニメーションなし)
	shader = LoadShader("Shaders/depthmap.vert", "Shaders/depthmap.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::DEPTH);

	// ジオメトリインスタンスを適用した描画用シェーダをロード
	shader = LoadShader("Shaders/GeometryInstance.vert", "Shaders/shadowmap.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::GEOMETRY_INSTANCE);

	// シャドウを適用した描画用シェーダをロード(アニメーションなし)
	shader = LoadShader("Shaders/shadowmap.vert", "Shaders/shadowmap.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::SHADOW);

	// デプスマップ焼き用シェーダをロード (アニメーションあり)
	shader = LoadShader("Shaders/SkinnedDepth.vert", "Shaders/depthmap.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::SKINNED_DEPTH);

	// シャドウを適用した描画用シェーダをロード(アニメーションあり)
	shader = LoadShader("Shaders/SkinnedShadow.vert", "Shaders/SkinnedShadow.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::SKINNED_DEPTH);

	return true;
}

Shader* GraphicsResourceManager::LoadShader(const std::string& _vertName, const std::string& _fragName)
{
	// 生成用シェーダー
	Shader* shader;
	// スプライトシェーダーの作成
	shader = new Shader();
	if (!shader->Load(_vertName, _fragName))
	{
		printf("シェーダー読み込み失敗\n");
		return nullptr;
	}

	return shader;
}

void GraphicsResourceManager::AddShaderMap(Shader* _shader, ShaderTag _shaderTag)
{
	//マップの中に追加するシェーダーのコンテナがあるかどうかを調べる
	auto stateMaps = shaders.find(_shaderTag);

	//あるとき
	if (stateMaps != shaders.end())
	{
		return;
	}
	else //ないとき
	{
		shaders[_shaderTag] = _shader;
	}
}
