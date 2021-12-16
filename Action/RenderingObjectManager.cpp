#pragma warning(disable:4996)
//-----------------------------------------------------------------------------
//	@brief	インクルード
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
@brief	Particle用頂点データのセット関数
*/
void RenderingObjectManager::SetParticleVertex()
{
	particleVertex->SetActive();
}

/*
@brief  コンストラクタ
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
@brief  デストラクタ
*/
RenderingObjectManager::~RenderingObjectManager()
{
}

/*
@brief  インスタンスを作成する
*/
void RenderingObjectManager::CreateInstance()
{
	// 作られていなかったら生成
	if (renderingObjectManager == nullptr)
	{
		renderingObjectManager = new RenderingObjectManager();
	}
}

/*
@brief  インスタンスを削除する
*/
void RenderingObjectManager::DeleteInstance()
{
	// 削除されていなかったら削除
	if (renderingObjectManager != nullptr)
	{
		delete renderingObjectManager;
		renderingObjectManager = nullptr;
	}
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool RenderingObjectManager::Initialize(int _screenWidth, int _screenHeight, bool _fullScreen)
{
	// スクリーンサイズ初期化
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを4.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
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

	// 3Dモデル用ビュー行列の設定
	view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(CameraProjectionFov),
		(float)screenWidth, (float)screenHeight, CameraProjectionNear, CameraProjectionFar);

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


	//undefineTexID = CreateTexture("Assets/sprite/noneTexture.png")->GetTextureID();

	//　HDRrendererの生成
	hdrRenderer = new HDRRenderer(screenWidth, screenHeight,4);
	geometryInstanceManager = new GeometryInstanceManager();
	// カリングのモード設定
	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	return true;
}

/*
@brief  終了処理
*/
void RenderingObjectManager::Shutdown()
{
	// vertexの後片付け
	delete particleVertex;
	delete spriteVerts;
	delete cubeVerts;

	// コンテキストとwindowの後片付け
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/*
@brief  ロードしたデータの解放
*/
void RenderingObjectManager::UnloadData()
{
}

/*
@brief  描画処理
*/
void RenderingObjectManager::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// デプスマップレンダリング
	BakeDepthMap();

	//シャドウマップ描画
	DrawShadowMap();

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
	// sprite用ビュー行列の設定
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj((float)screenWidth, (float)screenHeight);
	Shader* useShader = nullptr;
	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SPRITE);
	useShader->SetActive();
	useShader->SetMatrixUniform("uViewProj", viewProj);
	// すべてのスプライトの描画
	for (auto sprite : spriteComponents)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(useShader);
		}
	}

	// バッファを交換
	SDL_GL_SwapWindow(window);
}

/*
@brief  スプライトの追加
@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
*/
void RenderingObjectManager::AddSprite(SpriteComponent* _spriteComponent)
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

		// 検索した場所のiterの場所に挿入
		spriteComponents.insert(iter, _spriteComponent);
	}
}

/*
@brief スプライトの削除
@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
*/
void RenderingObjectManager::RemoveSprite(SpriteComponent* _spriteComponent)
{
	// 背景かどうかを取得
	bool isBackGround = _spriteComponent->GetIsBackGround();

	// 背景じゃなかったら
	if (isBackGround == false)
	{
		// 通常コンテナから探して削除
		auto iter = std::find(spriteComponents.begin(), spriteComponents.end(), _spriteComponent);
		spriteComponents.erase(iter);
	}

}

/*
@brief  パーティクルの追加
@param	_particleComponent　追加するParticleObjectクラスのポインタ
*/
void RenderingObjectManager::AddParticle(ParticleComponent * _particleComponent)
{
	// 描画順を取得
	int myDrawOrder = _particleComponent->GetDrawOrder();
	// 描画順に沿って追加
	// 今あるパーティクルから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
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
	// 検索した場所のiterの場所に挿入
	particleComponents.insert(iter, _particleComponent);
}

/*
@brief  スプライトの削除
@param	削除するParticleObjectクラスのポインタ
*/
void RenderingObjectManager::RemoveParticle(ParticleComponent * _particleComponent)
{
	// パーティクルコンテナから探して削除
	auto iter = std::find(particleComponents.begin(), particleComponents.end(), _particleComponent);
	particleComponents.erase(iter);
}

/*
@brief  メッシュコンポーネントの追加
@param	_meshComponent　追加するMeshComponentクラスのポインタ
*/
void RenderingObjectManager::AddMeshComponent(MeshComponent* _meshComponent)
{
	//メッシュデータにスケルトンデータがあれば
	if (_meshComponent->GetIsSkeltal())
	{
		// スキニングモデルとして生成
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		skeletalMeshComponents.emplace_back(sk);
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
void RenderingObjectManager::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	//メッシュデータにスケルトンデータがあれば
	if (_meshComponent->GetIsSkeltal())
	{
		// スキニングモデルコンテナから探して削除
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(skeletalMeshComponents.begin(), skeletalMeshComponents.end(), sk);
		skeletalMeshComponents.erase(iter);
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
@brief  Sprite用の頂点バッファとインデックスバッファの作成
*/
void RenderingObjectManager::CreateSpriteVerts()
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

/*
@brief  Particle用の頂点バッファとインデックスバッファの作成
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
@brief  キューブマップ(スカイボックス用)頂点配列定義
*/
void RenderingObjectManager::CreateCubeVerts()
{
	cubeVerts = new VertexArray();
	cubeVerts->CreateCubeVerts();
}

/*
@brief  シャドウマップの本描画関数
*/
void RenderingObjectManager::DrawShadowMap()
{

	Shader* useShader = nullptr;

	/* HDRとシャドウマップの処理開始 */
	// HDRレコーディング開始
	hdrRenderer->HdrRecordBegin();

	// スカイボックス描画
	if (activeSkyBox != nullptr)
	{
		useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SKYBOX);
		useShader->SetActive();
		
		// ゲームの空間に合わせるためのオフセット行列をセット
		Matrix4 offset = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
		useShader->SetMatrixUniform("u_offset", offset);

		// Uniformに逆行列をセット
		Matrix4 InvView = view;
		InvView.Invert();
		InvView.Transpose();
		useShader->SetMatrixUniform("u_invView", InvView);
		useShader->SetMatrixUniform("u_projection", projection);
		useShader->SetIntUniform("u_skybox", 0);

		activeSkyBox->Draw(useShader);
	}

	// 当たり判定デバッグBoxの表示
	PHYSICS->DebugShowBox();

	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::GEOMETRY_INSTANCE);
	//シャドウマップshaderをアクティブ
	useShader->SetActive();
	// ライトのカメラ情報
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	useShader->SetFloatUniform("uLuminance", 1.0f);

	// ディレクショナルライト
	useShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	useShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	useShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	useShader->SetMatrixUniform("view", view);
	useShader->SetMatrixUniform("projection", projection);

	// デプスマップをセット（メッシュ用）
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	useShader->SetIntUniform("depthMap", 4);
	useShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);
	geometryInstanceManager->PrepareModelMatrice();
	geometryInstanceManager->Draw(useShader);



	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SHADOW);

	//シャドウマップshaderをアクティブ
	useShader->SetActive();
	// ライトのカメラ情報
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	useShader->SetFloatUniform("uLuminance", 1.0f);

	// ディレクショナルライト
	useShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	useShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	useShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);

	useShader->SetMatrixUniform("view", view);
	useShader->SetMatrixUniform("projection", projection);

	// デプスマップをセット（メッシュ用）
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	useShader->SetIntUniform("depthMap", 4);

	useShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);


	// シェーダーに渡すライティング情報を更新する
	// すべてのメッシュの描画
	for (auto mc : meshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(useShader);
		}
	}


	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SKINNED_SHADOW);
	//シャドウマップshaderをアクティブ(skinnend)
	useShader->SetActive();
	// ライトのカメラ情報
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	// ディレクショナルライト
	useShader->SetVectorUniform("uDirLight.mDirection", LightDir);
	useShader->SetVectorUniform("uDirLight.mDiffuseColor", dirLight.diffuseColor);
	useShader->SetVectorUniform("uDirLight.mSpecColor", dirLight.specColor);
	useShader->SetFloatUniform("uLuminance", 1.0f);
	useShader->SetMatrixUniform("uViewProj", view * projection);
	// デプスマップをセット（スキニング用）
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
	// ライトのカメラ情報
	useShader->SetVectorUniform("uCameraPos", lightViewPos);
	// アンビエントライト
	useShader->SetVectorUniform("uAmbientLight", ambientLight);
	// ディレクショナルライト
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

/*
@brief  デプスマップ焼きこみ描画
*/
void RenderingObjectManager::BakeDepthMap()
{
	Shader* useShader = nullptr;

	// プレイヤーのポジションを参照してライト空間を作成する際のポジションを計算
	LightPos = Vector3(playerPos.x , playerPos.y , playerPos.z + ShiftLightPositionZ);

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


	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::DEPTH);
	// デプスマップ焼き用シェーダを有効化し、必要な値をシェーダにセット・シャドウをつけたいオブジェクトを描画する
	// メッシュモデルシェーダーアクティブ
	useShader->SetActive();
	useShader->SetMatrixUniform("lightSpaceMatrix", lightSpeceMatrix);

	// メッシュモデルの描画
	for (auto mc : meshComponents)
	{
		// 壁以外を深度マップに書き込み
		// ※壁の影を描画すると見た目上見づらかったため
		Tag checkTag = mc->GetOwner()->GetTag();

		if (mc->GetVisible() && checkTag != Tag::WALL)
		{
			mc->Draw(useShader);
		}
	}

	// ライト用プロジェクション作成
	lightProjection = Matrix4::CreateOrtho(LightProjectionWhidth, LightProjectionHight, LightProjectionNear, LightProjectionFar);
	// ビュー行列の更新
	lightView = Matrix4::CreateLookAt(LightPos, playerPos, Vector3::UnitX);
	// ライト空間行列を計算
	lightSpeceMatrix = lightView * lightProjection;

	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::SKINNED_DEPTH);

	// スキニングモデルシェーダーアクティブ
	useShader->SetActive();
	useShader->SetMatrixUniform("uLightSpaceMat", lightSpeceMatrix);

	// スキニングモデルの描画
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
@brief  Particle用の頂点バッファとインデックスバッファの作成
*/
void RenderingObjectManager::DrawParticle()
{
	// particleのコンテナをソート
	std::sort(particleComponents.begin(), particleComponents.end(), std::greater<ParticleComponent*>());

	// particleが0だったらスキップ
	if (particleComponents.size() == 0)
	{
		return;
	}

	// ブレンドモード初期状態取得
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = particleComponents.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// テクスチャID初期状態取得
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;
	viewProjectionMat = view * projection;

	Shader* useShader = nullptr;

	useShader = GRAPHICS_RESOURCE->FindUseShader(ShaderTag::PARTICLE);
	// シェーダーON
	useShader->SetActive();
	useShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// 全てのパーティクルのビルボード行列をセット
	(*itr)->SetBillboardMat(GetBillboardMatrix());


	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// すべてのパーティクルを描画
	glActiveTexture(GL_TEXTURE0);
	useShader->SetIntUniform("uTexture", 0);

	// ブレンドモードの変更
	ChangeBlendMode(blendType);
	// textureの変更
	ChangeTexture(nowTexture);

	// particleを描画
	for (auto particle : particleComponents)
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
				useShader->SetIntUniform("uTexture", 0);
				ChangeBlendMode(blendType);
			}

			// テクスチャ変更が必要なら変更する
			nowTexture = particle->GetTextureID();

			if (nowTexture != prevTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				useShader->SetIntUniform("uTexture", 0);
				ChangeTexture(nowTexture);
			}

			// パーティクル描画
			particle->Draw(useShader);

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
void RenderingObjectManager::SetLightUniforms(Shader* _shader, const Matrix4& _view)
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

/*
@brief  particleのブレンドモードを変更する
@param  blendType　変更するモード
*/
void RenderingObjectManager::ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM _blendType)
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

/*
@brief  textureを変更する
@param  changeTextureID　変更するtextureのID
*/
void RenderingObjectManager::ChangeTexture(int changeTextureID)
{
	// textureIDをバインド
	glBindTexture(GL_TEXTURE_2D, changeTextureID);
}

/*
@brief  ワールド空間のカメラ座標を計算
*/
Vector3 RenderingObjectManager::CalcCameraPos()
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

/*
@brief  画面全体を覆う頂点の定義
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