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
	// すべてのテクスチャのデータを解放
	for (auto texture : textures)
	{
		texture.second->Unload();
		delete texture.second;
	}

	textures.clear();

	// すべてのメッシュのデータを解放
	for (auto meshe : meshes)
	{
		meshe.second->Unload();
		delete meshe.second;
	}
	meshes.clear();

	// スケルトンの解放
	for (auto skeleton : skeletons)
	{
		delete skeleton.second;
	}
	skeletons.clear();

	// アニメーションの解放
	for (auto anim : anims)
	{
		delete anim.second;
	}
	anims.clear();

	// シェーダーの破棄
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

	// シェーダーのロード
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		//return false;
	}

	// カウントダウンタイム用texture生成
	CreateTimeFontTexture(MaxTimeFontTextures, TimeFontSize);
}

GraphicsResourceManager::~GraphicsResourceManager()
{
	// 後片付け
	ShutDown();
}

void GraphicsResourceManager::CreateTimeFontTexture(int _value, int _fontSize)
{
	// フォントの生成
	Font* font = CreateFont("Assets/Config/Fonts/impact.ttf");
	// 格納する可変長配列をリサイズ
	timeFontTextures.resize(_value);
	timeBlackFontTextures.resize(_value);
	timeRedFontTextures.resize(_value);

	// 最大値を用いてフォントの色ごとにその枚数textureを生成
	// 白色
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeFontTextures[i] = font->RenderText(str, Color::White, _fontSize);
	}

	// 黒色（バックフォント用（文字の影））
	for (int i = 0; i < _value; i++)
	{
		std::string str;
		str = std::to_string(i);
		timeBlackFontTextures[i] = font->RenderText(str, Color::Black, _fontSize);
	}

	// 赤色
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
	//すでに作成されてないか調べる
	auto itr = textures.find(_fileName);

	if (itr != textures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
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
	//すでに作成されてないか調べる
	auto itr = fonts.find(_fileName);

	if (itr != fonts.end())
	{
		font = itr->second;
	}
	//作成済みでない場合、新しくフォントを作成
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
	//すでに作成されてないか調べる
	std::string file(_fileName);
	auto iter = skeletons.find(file);
	if (iter != skeletons.end())
	{
		return iter->second;
	}
	else 	//作成済みでない場合、新しくスケルトンを作成
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
	//すでに作成されてないか調べる
	auto iter = anims.find(_fileName);
	if (iter != anims.end())
	{
		return iter->second;
	}
	else 	//作成済みでない場合、新しくアニメーションを作成
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
	//すでに作成されてないか調べる
	auto iter = meshes.find(_fileName);
	if (iter != meshes.end())
	{
		m = iter->second;
	}
	//作成済みでない場合、新しくメッシュを作成
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
	// 格納用シェーダー
	Shader* shader = nullptr;
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

	// ジオメトリインスタンスを適用した描画用シェーダをロード
	shader = LoadShader("Shaders/GeometryInstance.vert", "Shaders/shadowmap.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::GEOMETRY_INSTANCE);

	// デプスマップ焼き用シェーダをロード(アニメーションなし)
	shader = LoadShader("Shaders/depthmap.vert", "Shaders/depthmap.frag");
	// 格納
	AddShaderMap(shader, ShaderTag::DEPTH);

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
	AddShaderMap(shader, ShaderTag::SKINNED_SHADOW);

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


/*
@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（白）
@param	カウントダウンタイム
@return カウントダウンタイムごとのTimeTexture
*/
Texture* GraphicsResourceManager::GetTimeTexture(int _time)
{
	return timeFontTextures[_time + 1];
}

/*
@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（黒）
@param	カウントダウンタイム
@return カウントダウンタイムごとのTimeTexture
*/
Texture* GraphicsResourceManager::GetTimeBlackTexture(int _time)
{
	return timeBlackFontTextures[_time + 1];
}

/*
@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（赤）
@param	カウントダウンタイム
@return カウントダウンタイムごとのTimeTexture
*/
Texture* GraphicsResourceManager::GetTimeRedTexture(int _time)
{
	return timeRedFontTextures[_time + 1];
}

Shader* GraphicsResourceManager::FindUseShader(ShaderTag _shaderTag)
{
	//マップの中に追加するシェーダーのコンテナがあるかどうかを調べる
	auto stateMaps = shaders.find(_shaderTag);
	//あるとき
	if (stateMaps != shaders.end())
	{
		// 使用するシェーダーを返す
		return shaders[_shaderTag];
	}
	else //ないとき
	{
		return nullptr;
	}
}
