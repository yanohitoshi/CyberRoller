#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "GameObject.h"

// シングルトンなのでインスタンスのgetterを静的領域にdefineで定義
#define RENDERING_OBJECT_MANAGER RenderingObjectManager::GetInstance()

//平行光源用の構造体
struct DirectionalLight
{
	// 光の方向
	Vector3 direction;
	// 拡散反射色
	Vector3 diffuseColor;
	// 鏡面反射色
	Vector3 specColor;
};

/*
@enum textureステージの列挙
*/
enum class TextureStage
{
	// ディフーズマップ
	DIFFUSE_MAP,
	// ノーマルマップ
	NORMAL_MAP,
	// スペキュラマップ
	SPECULAR_MAP,
	// エミッシブマップ
	EMISSIVE_MAP,
	// シャドウマップ
	SHADOW_MAP
};

// クラスの前方宣言
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

// enumクラスの前置宣言
enum SceneState;

/*
@file Renderer.h
@brief 描画の進行を行うクラス
*/
class RenderingObjectManager
{
public:
	/*
	@brief  インスタンスを取得する
	@return Rendererクラスのインスタンス
	*/
	static RenderingObjectManager* GetInstance() { return renderingObjectManager; }

	/*
	@brief  インスタンスを作成する
	*/
	static void CreateInstance();

	/*
	@brief  インスタンスを削除する
	*/
	static void DeleteInstance();

	/*
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize(int _screenWidth, int _screenHeight, bool _fullScreen);
	/*
	@brief  終了処理
	*/
	void Shutdown();

	/*
	@brief  ロードしたデータの解放
	*/
	void UnloadData();

	/*
	@brief  描画処理
	*/
	void Draw();
	   
	/*
	@brief  スプライトの追加
	@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@brief スプライトの削除
	@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@brief  パーティクルの追加
	@param	_particleComponent　追加するParticleObjectクラスのポインタ
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@brief  スプライトの削除
	@param	削除するParticleObjectクラスのポインタ
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
	/*
	@brief  メッシュコンポーネントの追加
	@param	_meshComponent　追加するMeshComponentクラスのポインタ
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief  メッシュコンポーネントの削除
	@param	_meshComponent　削除するMeshComponentクラスのポインタ
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief	Particle用頂点データのセット関数
	*/
	void SetParticleVertex();

	// アクティブスカイボックス
	void SetActiveSkyBox(class CubeMapComponent* in_skyBox) { activeSkyBox = in_skyBox; }
	class CubeMapComponent* GetSkyBox() { return activeSkyBox; }
	class VertexArray* GetCubeMapVerts() { return cubeVerts; }

	void SetNowSceneState(SceneState _nowSceneState) { nowSceneState = _nowSceneState; }

private:

	//コンストラクタ、デストラクタの隠蔽
	/*
	@brief  コンストラクタ
	*/
	RenderingObjectManager();

	/*
	@brief  デストラクタ
	*/
	~RenderingObjectManager();

	SceneState nowSceneState;

	//自分のインスタンス
	static RenderingObjectManager* renderingObjectManager;
	SDL_Renderer* sdlRenderer;

	// HDR レンダラー
	HDRRenderer* hdrRenderer;

	// ジオメトリインスタンスmanager
	GeometryInstanceManager* geometryInstanceManager;

	/*
	@brief  シェーダーの読み込み
	@return true : 成功 , false : 失敗
	*/
	bool LoadShaders();
	
	/*
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
	void CreateSpriteVerts();
	
	/*
	@brief  Particle用の頂点バッファとインデックスバッファの作成
	*/
	void CreateParticleVerts();

	/*
	@brief  キューブマップ(スカイボックス用)頂点配列定義
	*/
	void CreateCubeVerts();

	/*
	@brief	時間制限用textureの生成
	@param	_value　最大値
	@param _fontSize　フォントサイズ
	*/
	void CreateTimeFontTexture(int _value,int _fontSize);

	/*
	@brief  シャドウマップの本描画関数
	*/
	void DrawShadow();

	/*
	@brief  デプスマップ焼きこみ描画
	*/
	void DepthRendering();

	/*
	@brief  背景の描画
	*/
	void DrawBackGround();

	/*
	@brief  Particle用の頂点バッファとインデックスバッファの作成
	*/
	void DrawParticle();

	/*
	@brief  光源情報をシェーダーの変数にセットする
	@param  _shader セットするShaderクラスのポインタ
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& view);
	
	/*
	@brief  画面全体を覆う頂点の定義
	@param  vao Vertex Buffer Object
	*/
	void screenVAOSetting(unsigned int& vao);

	/*
	@brief  particleのブレンドモードを変更する
	@param  blendType　変更するモード
	*/
	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM _blendType);
	
	/*
	@brief  textureを変更する
	@param  changeTextureID　変更するtextureのID
	*/
	void ChangeTexture(int changeTextureID);
	
	/*
	@brief  ワールド空間のカメラ座標を計算
	*/
	Vector3 CalcCameraPos();

	// スケルトンデータ
	std::unordered_map<std::string, class Skeleton*> skeletons;
	// アニメーションデータ
	std::unordered_map<std::string, class Animation*> anims;    

	//ファイル名でメッシュを取得するための連想配列
	std::unordered_map<std::string, Mesh*> meshes;

	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> meshComponents;
	//カラーチェンジコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> colorChangeMeshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> sprites;
	//背景画像用スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> backGroundSprites;

	//パーティクルのポインタ
	std::vector<ParticleComponent*> particles;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*>textures;
	// スケルトンメッシュの描画に使われる
	std::vector<class SkeletalMeshComponent*>skeletalMeshes;   
	// 色を変えるメッシュの描画に使われる
	std::vector<class ChangeColorMeshComponent*>changeColorMeshes;

	// フォントマップ
	std::unordered_map<std::string, class Font*> fonts;

	// 時間表示用のフォントtexture
	// 白色
	std::vector<Texture*> timeFontTextures;
	// 黒色
	std::vector<Texture*> timeBlackFontTextures;
	// 赤色
	std::vector<Texture*> timeRedFontTextures;

	// キューブマップ
	class CubeMapComponent* activeSkyBox; // 有効な(描画する)スカイボックス
	//クラスのポインタ
	//スプライト
	Shader* spriteShader;
	VertexArray* spriteVerts;

	// スカイボックス用シェーダ
	Shader* skyboxShader;

	// スイッチ用シェーダー
	Shader* switchShader;
	// ジオメトリインスタンス用シェーダー
	Shader* geometryInstanceShader;
	//スキンメッシュ
	Shader*  mSkinnedShader;  

	//shadowマップ関連シェーダー
	//shadow用（メッシュ）
	Shader* depthMapShader;
	Shader* shadowMapShader;

	//shadow用（スキンメッシュ）
	Shader* skinnedDepthMapShader;
	Shader* skinnedShadowMapShader;

	//デバック用シェーダー
	Shader* debugShader;

	//パーティクル
	Shader* particleShader;
	// パーティクル用頂点定義
	VertexArray* particleVertex;
	// キューブ頂点配列
	VertexArray* cubeVerts;

	//環境光
	Vector3 ambientLight;
	//平行光源
	DirectionalLight dirLight;
	//ウィンドウ
	SDL_Window* window;
	//コンテキスト
	SDL_GLContext context;

	// カメラの視野角
	const float CameraProjectionFov;
	// カメラプロジェクションの近距離
	const float CameraProjectionNear;
	// カメラプロジェクションの遠距離
	const float CameraProjectionFar;

	// シャドウマップの横幅
	const unsigned int ShadowWidth;
	// シャドウマップの縦幅
	const unsigned int ShadowHeight;

	// ライトの位置のZ軸をプレイヤーの位置からずらす値
	const float ShiftLightPositionZ;
	// ライトの位置のX軸をプレイヤーの位置からずらす値
	const float ShiftLightPositionX;

	// ライトプロジェクション行列生成用定数
	// ライトプロジェクションの幅の定数
	const float LightProjectionWhidth;
	// ライトプロジェクションの高さの定数
	const float LightProjectionHight;
	// ライトプロジェクションの近距離の定数
	const float LightProjectionNear;
	// ライトプロジェクションの遠距離の定数
	const float LightProjectionFar;
	// 制限時間用フォントtextureの最大数（作りたい数字の最大値）
	const int MaxTimeFontTextures;
	// 制限時間用フォントのサイズ
	const int TimeFontSize;

	//スクリーンの横幅
	int screenWidth;
	//スクリーンの縦幅
	int screenHeight;

	// 未設定テクスチャの場合に割り当てられる黒色テクスチャ
	unsigned int undefineTexID;
	//デプスマップ
	unsigned int depthMapFBO;
	// デプスマップtextureID
	unsigned int depthMap;

	// プレイヤーの位置保存用
	Vector3 playerPos;
	// ライトのポジション
	Vector3 LightPos;
	// ライトの向き
	Vector3 LightDir;
	// カメラの前方向ベクトル
	Vector3 cameraForwardVec;
	// ライトビューのポジション
	Vector3 lightViewPos;

	// ライトの行列群
	// プロジェクション、ビュー、ライト空間
	Matrix4 lightProjection;
	Matrix4 lightView;
	Matrix4 lightSpeceMatrix;

	//ビュー行列
	Matrix4 view;
	//射影行列
	Matrix4 projection;
	//ビルボード行列
	Matrix4 billboardMat;


public://ゲッターセッター

	/*
	@brief  テクスチャの取得
	@param	_fileName　取得したいテクスチャのファイル名
	@return Textureクラスのポインタ
	*/
	GeometryInstanceManager* GetGeometryInstanceManager() { return geometryInstanceManager; }

	/*
	@brief  テクスチャの取得
	@param	_fileName　取得したいテクスチャのファイル名
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(const std::string& _fileName);

	/*
	@brief  フォントの取得
	@param	_fileName　取得したいフォントのファイル名
	@return Fontクラスのポインタ
	*/
	Font* GetFont(const std::string& _fileName);

	/*
	@brief  スケルトンモデルの取得
	@param _fileName モデルへのアドレス
	@return スケルトンモデルクラスのポインタ
	*/
	const class Skeleton* GetSkeleton(const char* _fileName);
	
	/*
	@brief  アニメーションの取得
	@param _fileName アニメーションへのアドレス
	@return スケルトンアニメーションクラスのポインタ
	*/
	const class Animation* GetAnimation(const char* _fileName, bool _loop);

	/*
	@brief  メッシュの取得
	@param	_fileName 取得したいメッシュのファイル名
	@return Meshクラスのポインタ
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@brief	平行光源の構造体を取得する
	@return	DirectionalLight（平行光源の構造体）
	*/
	DirectionalLight& GetDirectionalLight() { return dirLight; }

	/*
	@brief	スクリーンの横幅を取得する
	@return	スクリーンの横幅
	*/
	int GetScreenWidth() const { return screenWidth; }

	/*
	@brief	スクリーンの縦幅を取得する
	@return	スクリーンの縦幅
	*/
	int GetScreenHeight() const { return screenHeight; }

	/*
	@brief	View行列のgetter
	@return View行列
	*/
	Matrix4 GetViewMatrix() const { return view; };


	/*
	@brief	Projection行列のgetter
	@return Projection行列
	*/
	Matrix4 GetProjectionMatrix() { return projection; }

	/*
	@brief  SDL_Rendererを取得する
	@return SDL_Rendererクラスのポインタ
	*/
	SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }
	unsigned int GetUndefineTexID() { return undefineTexID; }

	/*
	@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（白）
	@param	カウントダウンタイム
	@return カウントダウンタイムごとのTimeTexture
	*/
	Texture* GetTimeTexture(int _time);

	/*
	@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（黒）
	@param	カウントダウンタイム
	@return カウントダウンタイムごとのTimeTexture
	*/
	Texture* GetTimeBlackTexture(int _time);

	/*
	@brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（赤）
	@param	カウントダウンタイム
	@return カウントダウンタイムごとのTimeTexture
	*/
	Texture* GetTimeRedTexture(int _time);

	/*
	@brief	ビュー行列を設定する
	@param	_view ビュー行列
	*/
	void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/*
	@brief	環境光を設定する
	@param	_ambient Vector3（環境光を表す）
	*/
	void SetAmbientLight(Vector3& _ambient) { ambientLight = _ambient; }

	/*
	@brief	プレイヤーのポジションをセットするsetter
	@param	プレイヤーのポジション
	*/
	void SetPlayerPositon(Vector3 _pos) { playerPos = _pos; }
	/*
	@brief	カメラの前方ベクトルをセットするsetter
	@param	カメラの前方ベクトル
	*/
	void SetCameraForawrd(Vector3 _vec) { cameraForwardVec = _vec; }

};