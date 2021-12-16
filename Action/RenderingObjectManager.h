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
@brief 描画の進行とリソース管理を行うクラス
	   本来ならば、描画の進行とリソース管理はクラスを分けて管理するべきだが、
	   今回は、高速化のため1つのクラスにまとめて実装しました。
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

private:

	/*
	@brief  コンストラクタ
	*/
	RenderingObjectManager();

	/*
	@brief  デストラクタ
	*/
	~RenderingObjectManager();

	//自分のインスタンス
	static RenderingObjectManager* renderingObjectManager;
	SDL_Renderer* sdlRenderer;

	// HDR レンダラー
	HDRRenderer* hdrRenderer;

	// ジオメトリインスタンスmanager
	GeometryInstanceManager* geometryInstanceManager;

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
	@brief  シャドウマップの本描画関数
	*/
	void DrawShadowMap();

	/*
	@brief  デプスマップ焼きこみ描画
	*/
	void BakeDepthMap();

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


	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> meshComponents;
	//カラーチェンジコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> colorChangeMeshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> spriteComponents;
	//パーティクルのポインタ
	std::vector<ParticleComponent*> particleComponents;
	// スケルトンメッシュの描画に使われる
	std::vector<class SkeletalMeshComponent*>skeletalMeshComponents;
	// キューブマップ
	class CubeMapComponent* activeSkyBox; // 有効な(描画する)スカイボックス

	// スプライトの頂点配列
	VertexArray* spriteVerts;
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

	// ライトプロジェクションの幅の定数
	const float LightProjectionWhidth;
	// ライトプロジェクションの高さの定数
	const float LightProjectionHight;
	// ライトプロジェクションの近距離の定数
	const float LightProjectionNear;
	// ライトプロジェクションの遠距離の定数
	const float LightProjectionFar;


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


public: //ゲッターセッター

	/*
	@brief  ジオメトリインスタンスを管理しているクラスを取得
	@return ジオメトリインスタンスを管理しているクラスのポインタ
	*/
	GeometryInstanceManager* GetGeometryInstanceManager() { return geometryInstanceManager; }

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
	Matrix4 GetProjectionMatrix() const { return projection; }

	/*
	@brief  SDL_Rendererを取得する
	@return SDL_Rendererクラスのポインタ
	*/
	SDL_Renderer* GetSDLRenderer() const { return sdlRenderer; }
	unsigned int GetUndefineTexID() const { return undefineTexID; }

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
	
	// アクティブスカイボックス
	void SetActiveSkyBox(class CubeMapComponent* in_skyBox) { activeSkyBox = in_skyBox; }

	/*
	@brief	使用するCubeMapComponentクラスのポインタを取得
	@return	使用するCubeMapComponentクラスのポインタ
	*/
	class CubeMapComponent* GetSkyBox() { return activeSkyBox; }

	/*
	@brief	キューブマップで使用するVertexArrayを取得
	@param	キューブマップで使用するVertexArray
	*/
	class VertexArray* GetCubeMapVerts() { return cubeVerts; }
};