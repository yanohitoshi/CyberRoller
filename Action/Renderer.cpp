#pragma warning(disable:4996)

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>
#include <fstream>
#include <sstream>
#include <document.h>
#include "Skeleton.h"
#include "Animation.h"
#include "SkeletalMeshComponent.h"
#include "CubeMapComponent.h"
#include "Font.h"
#include "GameObject.h"
#include "MainCameraObject.h"
#include "HDRRenderer.h"

Renderer* Renderer::renderer = nullptr;

void Renderer::SetParticleVertex()
{
	particleVertex->SetActive();
}

Renderer::Renderer()
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
	, CameraProjectionFov(70.0f)
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

Renderer::~Renderer()
{
}

/*
@brief  インスタンスを作成する
*/
void Renderer::CreateInstance()
{
	// 作られていなかったら生成
	if (renderer == nullptr)
	{
		renderer = new Renderer();
	}
}

/*
@brief  インスタンスを削除する
*/
void Renderer::DeleteInstance()
{
	// 削除されていなかったら削除
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Renderer::Initialize(float _screenWidth, float _screenHeight, bool _fullScreen)
{
	// スクリーンサイズ初期化
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//ウィンドウの作成
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
		printf("SDLRendererの作成に失敗 : %s", SDL_GetError());
		return false;
	}

	// OpenGLのコンテキストを作成
	context = SDL_GL_CreateContext(window);

	// GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// 一部のプラットフォームで出る無害なエラーコードをクリアする
	glGetError();

	// シェーダーのロード
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}


	//スプライト用の頂点配列を作成
	CreateSpriteVerts();

	CreateParticleVerts();

	CreateCubeVerts();

	// SDL_ttfの初期化
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}


	undefineTexID = GetTexture("Assets/noneTexture.png")->GetTextureID();

	//　HDRrendererの生成
	hdrRenderer = new HDRRenderer(screenWidth, screenHeight,4);

	// カリングのモード設定
	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	// カウントダウンタイム用texture生成
	CreateTimeFontTexture(MaxTimeFontTextures, TimeFontSize);

	return true;
}

/*
@brief  終了処理
*/
void Renderer::Shutdown()
{
	//shaderとvertexの後片付け
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

	//コンテキストとwindowの後片付け
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/*
@brief  ロードしたデータの解放
*/
void Renderer::UnloadData()
{
	// すべてのテクスチャのデータを解放
	for (auto i : textures)
	{
		i.second->Unload();
		delete i.second;
	}
	textures.clear();

	// すべてのメッシュのデータを解放
	for (auto i : meshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// スケルトンの解放
	for (auto s : skeletons)
	{
		delete s.second;
	}
	// アニメーションの解放
	for (auto a : anims)
	{
		delete a.second;
	}

	meshes.clear();
	skeletons.clear();
	anims.clear();
}

/*
@brief  描画処理
*/
void Renderer::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// デプスマップレンダリング
	DepthRendering();

	//シャドウマップ描画
	DrawShadow();

	// particle描画
	DrawParticle();

	// UI系スプライトコンポーネントの描画
	// アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	// デプスバッファ法を無効にする
	glDisable(GL_DEPTH_TEST);


	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	spriteShader->SetActive();
	spriteVerts->SetActive();
	// すべてのスプライトの描画
	for (auto sprite : sprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(spriteShader);
		}
	}

	// バッファを交換
	SDL_GL_SwapWindow(window);
}


/*
@brief  スプライトの追加
@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
*/
void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// 背景かどうかを取得
	bool isBackGround = _spriteComponent->GetIsBackGround();
	// 描画順を取得
	int myDrawOrder = _spriteComponent->GetDrawOrder();

	// 背景じゃなかったら通常のコンテナに格納
	if (isBackGround == false)
	{
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

	// 背景だったら背景用ののコンテナに格納
	if (isBackGround == true)
	{
		// 描画順に沿って追加
		// 今あるスプライトから挿入する場所の検索
		// (DrawOrderが小さい順番に描画するため)
		auto iter = backGroundSprites.begin();
		for (;
			iter != backGroundSprites.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		// 検索した場所のiterの場所に挿入
		backGroundSprites.insert(iter, _spriteComponent);
	}
}

/*
@brief スプライトの削除
@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
*/
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	// 背景かどうかを取得
	bool isBackGround = _spriteComponent->GetIsBackGround();

	// 背景じゃなかったら
	if (isBackGround == false)
	{
		// 通常コンテナから探して削除
		auto iter = std::find(sprites.begin(), sprites.end(), _spriteComponent);
		sprites.erase(iter);
	}

	// 背景だったら
	if (isBackGround == true)
	{
		// 背景コンテナから探して削除
		auto iter = std::find(backGroundSprites.begin(), backGroundSprites.end(), _spriteComponent);
		backGroundSprites.erase(iter);
	}

}


/*
@brief  パーティクルの追加
@param	_particleComponent　追加するParticleObjectクラスのポインタ
*/
void Renderer::AddParticle(ParticleComponent * _particleComponent)
{
	// 描画順を取得
	int myDrawOrder = _particleComponent->GetDrawOrder();
	// 描画順に沿って追加
	// 今あるパーティクルから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
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
	// 検索した場所のiterの場所に挿入
	particles.insert(iter, _particleComponent);
}

/*
@brief  スプライトの削除
@param	削除するParticleObjectクラスのポインタ
*/
void Renderer::RemoveParticle(ParticleComponent * _particleComponent)
{
	// パーティクルコンテナから探して削除
	auto iter = std::find(particles.begin(), particles.end(), _particleComponent);
	particles.erase(iter);
}

/*
@brief  メッシュコンポーネントの追加
@param	_meshComponent　追加するMeshComponentクラスのポインタ
*/
void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	//メッシュデータにスケルトンデータがあれば
	if (_meshComponent->GetIsSkeltal())
	{
		// スキニングモデルとして生成
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		skeletalMeshes.emplace_back(sk);
	}
	else if(_meshComponent->GetIsColorChange() == true) // 途中で色の変更をおこなうメッシュだったら
	{
		// 色変更適用シェーダーを用いるモデルとして格納
		colorChangeMeshComponents.emplace_back(_meshComponent);
	}
	else
	{
		// 通常モデルコンテナに格納
		meshComponents.emplace_back(_meshComponent);
	}
}


/*
@brief  メッシュコンポーネントの削除
@param	_meshComponent　削除するMeshComponentクラスのポインタ
*/
void Renderer::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	//メッシュデータにスケルトンデータがあれば
	if (_meshComponent->GetIsSkeltal())
	{
		// スキニングモデルコンテナから探して削除
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(skeletalMeshes.begin(), skeletalMeshes.end(), sk);
		skeletalMeshes.erase(iter);
	}
	else if (_meshComponent->GetIsColorChange()) // 途中で色の変更をおこなうメッシュだったら
	{
		// 色変更適用コンテナから削除
		auto iter = std::find(colorChangeMeshComponents.begin(), colorChangeMeshComponents.end(), _meshComponent);
		colorChangeMeshComponents.erase(iter);
	}
	else
	{
		// 通常コンテナから削除
		auto iter = std::find(meshComponents.begin(), meshComponents.end(), _meshComponent);
		meshComponents.erase(iter);
	}
}


/*
@param _fileName モデルへのアドレス
@return スケルトンモデルの取得
*/
const Skeleton * Renderer::GetSkeleton(const char * _fileName)
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

/*
@param _fileName アニメーションへのアドレス
@return スケルトンアニメーションの取得
*/
const Animation * Renderer::GetAnimation(const char * _fileName, bool _loop)
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
@brief  テクスチャの取得
@param	_fileName　取得したいテクスチャのファイル名
@return Textureクラスのポインタ
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
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

Font* Renderer::GetFont(const std::string& _fileName)
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

/*
@brief  メッシュの取得
@param	_fileName 取得したいメッシュのファイル名
@return Meshクラスのポインタ
*/
Mesh* Renderer::GetMesh(const std::string &_fileName)
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

/*
@brief  シェーダーの読み込み
@return true : 成功 , false : 失敗
*/
bool Renderer::LoadShaders()
{
	// スプライトシェーダーの作成
	spriteShader = new Shader();
	if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	spriteShader->SetActive();
	// sprite用ビュー行列の設定
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);

	// 3Dモデル用ビュー行列の設定
	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(CameraProjectionFov),
		screenWidth, screenHeight, CameraProjectionNear, CameraProjectionFar);

	// switch用シェーダーの作成(色変更可能シェーダー)
	switchShader = new Shader();
	if (!switchShader->Load("Shaders/shadowmap.vert", "Shaders/switch.frag"))
	{
		return false;
	}
	switchShader->SetActive();
	switchShader->SetMatrixUniform("uViewProj", view * projection);

	skyboxShader = new Shader();
	if (!skyboxShader->Load("Shaders/gBuffer_SkyBox.vert", "Shaders/gBuffer_SkyBox.frag"))
	{
		return false;
	}

	//particleシェーダー
	particleShader = new Shader();
	if (!particleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}

	// シャドウ用フレームバッファオブジェクトを作成・デプスマップを生成し、シャドウバッファにアタッチ
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		ShadowWidth, ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// depthMapFBOにデプステクスチャをアタッチする
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// デプスマップ焼き用シェーダ(アニメーションなし)
	depthMapShader = new Shader();
	if (!depthMapShader->Load("Shaders/depthmap.vert", "Shaders/depthmap.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}
	// シャドウを適用した描画用シェーダ作成(アニメーションなし)
	shadowMapShader = new Shader();
	if (!shadowMapShader->Load("Shaders/shadowmap.vert", "Shaders/shadowmap.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}

	// デプスマップ焼き用シェーダ (アニメーションあり)
	skinnedDepthMapShader = new Shader();
	if (!skinnedDepthMapShader->Load("Shaders/SkinnedDepth.vert", "Shaders/depthmap.frag"))
	{
		printf("シェーダー読み込み失敗depth\n");
	}
	// シャドウを適用した描画用シェーダ作成 (アニメーションあり)
	skinnedShadowMapShader = new Shader();
	if (!skinnedShadowMapShader->Load("Shaders/SkinnedShadow.vert", "Shaders/SkinnedShadow.frag"))
	{
		printf("シェーダー読み込み失敗shadow\n");
	}

	return true;
}

/*
@brief  Sprite用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	spriteVerts = new VertexArray(vertices, 4, indices, 6);
}

// パーティクル頂点作成
void Renderer::CreateParticleVerts()
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

void Renderer::CreateCubeVerts()
{
	cubeVerts = new VertexArray();
	cubeVerts->CreateCubeVerts();
}

void Renderer::CreateTimeFontTexture(int _value, int _fontSize)
{
	// フォントの生成
	Font* font = GetFont("Assets/Config/Fonts/impact.ttf");
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
		timeFontTextures[i] = font->RenderText(str,Color::White, _fontSize);
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

Texture* Renderer::GetTimeTexture(int _time)
{
	return timeFontTextures[_time + 1];
}

Texture* Renderer::GetTimeBlackTexture(int _time)
{
	return timeBlackFontTextures[_time + 1];
}

Texture* Renderer::GetTimeRedTexture(int _time)
{
	return timeRedFontTextures[_time + 1];
}

void Renderer::DrawShadow()
{

	/* HDRとシャドウマップの処理開始 */
	// HDRレコーディング開始
	hdrRenderer->HdrRecordBegin();

	// シーンがタイトルだったら
	if (nowSceneState == SceneState::TITLE_SCENE)
	{
		// タイトルの背景を描画
		DrawBackGround();
	}

	// スカイボックス描画
	if (activeSkyBox != nullptr)
	{
		skyboxShader->SetActive();
		
		// ゲームの空間に合わせるためのオフセット行列をセット
		Matrix4 offset = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
		skyboxShader->SetMatrixUniform("u_offset", offset);

		// Uniformに逆行列をセット
		Matrix4 InvView = view;
		InvView.Invert();
		InvView.Transpose();
		skyboxShader->SetMatrixUniform("u_invView", InvView);
		skyboxShader->SetMatrixUniform("u_projection", projection);
		skyboxShader->SetIntUniform("u_skybox", 0);

		activeSkyBox->Draw(skyboxShader);
	}

	//シャドウマップshaderをアクティブ
	shadowMapShader->SetActive();
	// ライトのカメラ情報
	shadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	shadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	shadowMapShader->SetFloatUniform("uLuminance", 1.0f);

	// ディレクショナルライト
	shadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	shadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	shadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	shadowMapShader->SetMatrixUniform("view", view);
	shadowMapShader->SetMatrixUniform("projection", projection);

	// デプスマップをセット（メッシュ用）
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	shadowMapShader->SetIntUniform("depthMap", 4);

	shadowMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	// シェーダーに渡すライティング情報を更新する
	// すべてのメッシュの描画
	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(shadowMapShader);
		}
	}

	//シャドウマップshaderをアクティブ(skinnend)
	skinnedShadowMapShader->SetActive();
	// ライトのカメラ情報
	skinnedShadowMapShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	skinnedShadowMapShader->SetVectorUniform("uAmbientLight", ambientLight);
	// ディレクショナルライト
	skinnedShadowMapShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	skinnedShadowMapShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	skinnedShadowMapShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);
	skinnedShadowMapShader->SetFloatUniform("uLuminance", 1.0f);
	skinnedShadowMapShader->SetMatrixUniform("uViewProj", view * projection);
	// デプスマップをセット（スキニング用）
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
	// ライトのカメラ情報
	switchShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	switchShader->SetVectorUniform("uAmbientLight", ambientLight);
	// ディレクショナルライト
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

	// HDRレコーデイング終了
	hdrRenderer->HdrRecordEnd();

	/* HDR Bloom の作成と合成 */
	// ガウスぼかしの生成
	hdrRenderer->HiBrightBlurCreate();
	// ガウスぼかしした画像とHDRを最終合成
	hdrRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBufferにレンダリングしたときのDepth情報をスクリーンにコピー
	hdrRenderer->CopyDepthToScreen();

}

void Renderer::DepthRendering()
{

	// プレイヤーのポジションを参照してライト空間を作成する際のポジションを計算
	LightPos = Vector3(playerPos.x /*- ShiftLightPositionX*/, playerPos.y /*- 500.0f*/, playerPos.z + ShiftLightPositionZ);

	// ディレクショナルライトからライトの方向を取得
	LightDir = dirLight.direction;
	// 正規化
	LightDir.Normalize();
	// ライト用プロジェクション作成
	lightProjection = Matrix4::CreateOrtho(LightProjectionWhidth, LightProjectionHight, LightProjectionNear, LightProjectionFar);
	// ビュー行列の更新
	lightView = Matrix4::CreateLookAt(LightPos, Vector3(playerPos.x - 10.0f, playerPos.y - 10.0f, playerPos.z), Vector3::UnitX);
	// ライト空間行列を計算
	lightSpeceMatrix = lightView * lightProjection;

	// ビューポートを深度マップサイズに設定する
	glViewport(0, 0, ShadowWidth, ShadowHeight);
	// シャドウフレームバッファをバインド
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

	glClear(GL_DEPTH_BUFFER_BIT);

	// デプスマップ焼き用シェーダを有効化し、必要な値をシェーダにセット・シャドウをつけたいオブジェクトを描画する
	// メッシュモデルシェーダーアクティブ
	depthMapShader->SetActive();
	depthMapShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	// メッシュモデルの描画
	for (auto mc : meshComponents)
	{
		// 壁以外を深度マップに書き込み
		// ※壁の影を描画すると見た目上見づらかったため
		Tag chackTag = mc->GetOwner()->GetTag();

		if (mc->GetVisible() && chackTag != Tag::WALL)
		{
			mc->Draw(depthMapShader);
		}
	}

	// ライト用プロジェクション作成
	lightProjection = Matrix4::CreateOrtho(LightProjectionWhidth, LightProjectionHight, LightProjectionNear, LightProjectionFar);
	// ビュー行列の更新
	lightView = Matrix4::CreateLookAt(LightPos, playerPos, Vector3::UnitX);
	// ライト空間行列を計算
	lightSpeceMatrix = lightView * lightProjection;

	// スキニングモデルシェーダーアクティブ
	skinnedDepthMapShader->SetActive();
	skinnedDepthMapShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	// スキニングモデルの描画
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

void Renderer::DrawBackGround()
{
	// アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// スプライトコンポーネントの描画(背景)
	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	spriteShader->SetActive();
	spriteVerts->SetActive();
	glActiveTexture(GL_TEXTURE0);
	spriteShader->SetIntUniform("uTexture", 0);

	// すべてのスプライトの描画
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

void Renderer::DrawParticle()
{
	// particleのコンテナをソート
	std::sort(particles.begin(), particles.end(), std::greater<ParticleComponent*>());

	// particleが0だったらスキップ
	if (particles.size() == 0)
	{
		return;
	}

	// ブレンドモード初期状態取得
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = particles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// テクスチャID初期状態取得
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;
	viewProjectionMat = view * projection;

	// シェーダーON
	particleShader->SetActive();
	particleShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// 全てのパーティクルのビルボード行列をセット
	(*itr)->SetBillboardMat(GetBillboardMatrix());


	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// すべてのパーティクルを描画
	glActiveTexture(GL_TEXTURE0);
	particleShader->SetIntUniform("uTexture", 0);

	// ブレンドモードの変更
	ChangeBlendMode(blendType);
	// textureの変更
	ChangeTexture(nowTexture);

	// particleを描画
	for (auto particle : particles)
	{
		// 描画する状態だったら
		if (particle->GetVisible())
		{
			//ブレンドモード変更が必要なら変更する
			blendType = particle->GetBlendType();
			blendType = particle->GetBlendType();

			if (blendType != prevType)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeBlendMode(blendType);
			}

			// テクスチャ変更が必要なら変更する
			nowTexture = particle->GetTextureID();

			if (nowTexture != prevTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				particleShader->SetIntUniform("uTexture", 0);
				ChangeTexture(nowTexture);
			}

			// パーティクル描画
			particle->Draw(particleShader);

			// 前回描画状態として保存
			prevType = blendType;
			prevTexture = nowTexture;
		}
	}

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}


/*
@brief  光源情報をシェーダーの変数にセットする
@param _shader セットするShaderクラスのポインタ
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// ビュー行列を逆行列にする
	Matrix4 invView = _view;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// 環境光の設定
	_shader->SetVectorUniform("uAmbientLight", ambientLight);
	// 平行光源の設定
	_shader->SetVectorUniform("uDirLight.mDirection",
		dirLight.direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		dirLight.diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		dirLight.specColor);
}

void Renderer::ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM _blendType)
{
	// PARTICLE_BLEND_ENUMのタイプを参照
	switch (_blendType)
	{
	case ParticleComponent::PARTICLE_BLEND_ENUM_ADD:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //加算合成
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //乗算合成
		break;
	default:
		break;
	}
}

void Renderer::ChangeTexture(int changeTextureID)
{
	// textureIDをバインド
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

// ワールド空間のカメラ座標を計算
Vector3 Renderer::CalcCameraPos()
{
	// ビュー行列よりワールドでのカメラ位置算出
	Matrix4 transMat = view;

	// ビュー行列の移動成分抜き取る
	Vector3 v;
	v.x = -1.0f * view.mat[3][0];
	v.y = -1.0f * view.mat[3][1];
	v.z = -1.0f * view.mat[3][2];

	//移動成分を取り除いたあと転置して、回転部分の逆変換を作る
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}


// 画面全体を覆う頂点定義
void Renderer::screenVAOSetting(unsigned int& vao)
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