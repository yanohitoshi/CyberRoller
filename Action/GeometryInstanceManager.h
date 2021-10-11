#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <unordered_map>
#include "GameObject.h"

/// <summary>
/// ジオメトリインスタンスの種類
/// </summary>
enum class GeometryInstanceType
{
	G_GROUND,
	G_CRYSTAL,
	G_LIGHT,
	G_NEEDLE,
	G_NEEDLE_PANEL,
	G_PUDH_BOARD,
	G_PUDH_BOX,
	G_JUMP_SWITCH,
	G_BASE_SWITCH,
	G_MOVE_WALL,
	gBossEnemyBullet,
	gHPPortion,
	gSPPortion
};

class GeometryInstanceManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GeometryInstanceManager() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GeometryInstanceManager();

	/// <summary>
	/// インスタンス用のメッシュを設定する
	/// </summary>
	/// <param name="_mesh">登録するメッシュ</param>
	/// <param name="_maxInstanceNum">最大インスタンス数</param>
	/// <param name="_type">ジオメトリインスタンスの種類</param>
	void SetInstanceMesh(class Mesh* _mesh, const unsigned int _maxInstanceNum, const GeometryInstanceType _type);

	/// <summary>
	/// 行列バッファの更新
	/// </summary>
	void PrepareModelMatrice();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shader">シェーダー</param>
	void Draw(class Shader* _shader);

	/// <summary>
	/// ジオメトリインスタンス用のアクターを追加
	/// </summary>
	/// <param name="_actor">追加するアクター</param>
	/// <param name="_type">追加するアクターのジオメトリインスタンスの種類</param>
	void AddGeometryInstanceActor(class GameObject* _gameObject, GeometryInstanceType _type);

	/// <summary>
	/// ジオメトリインスタンス用のアクターの削除
	/// </summary>
	/// <param name="_actor">削除するアクター</param>
	/// <param name="_type">削除するアクターのジオメトリインスタンスの種類</param>
	void RemoveGeometryInstanceActor(class GameObject* _gameObject, GeometryInstanceType _type);

	/// <summary>
	/// ジオメトリインスタンスの種類に応じてメッシュを返す
	/// </summary>
	/// <param name="_type">ジオメトリインスタンスの種類</param>
	class Mesh* GetMesh(GeometryInstanceType _type) { return mGeometryInstanceActorInfoMap[_type].mMesh; }

	/// <summary>
	/// ジオメトリインスタンスのアクターを格納するマップをクリア
	/// </summary>
	void ClearGeometryInstanceActorMap();

private:

	/// <summary>
	/// ジオメトリインスタンスのアクター情報の構造体
	/// </summary>
	struct GeometryInstanceActorInfo
	{
		// インスタンス最大数​
		unsigned int mMaxInstanceNum;
		// インデックスバッファにあるインデックスの数
		unsigned int mNumIndices;
		//頂点配列オブジェクトのOpenGL ID
		unsigned int mVertexArray;
		//行列バッファ
		float* mModelMatrice;
		//インスタンス描画可能なID
		unsigned int mInstanceVAO;
		//メッシュのポインタ
		class Mesh* mMesh;

	};

	/// <summary>
	/// シェーダーにテクスチャをセット
	/// </summary>
	/// <param name="_shader">シェーダー</param>
	/// <param name="_type">ジオメトリインスタンスの種類</param>
	void SetTextureToShader(Shader* _shader, GeometryInstanceType _type);

	//ジオメトリインスタンスのアクターを格納するマップ
	std::unordered_map<GeometryInstanceType, std::vector<GameObject*>> mGeometryInstanceActorMap;
	//ジオメトリインスタンスのアクター情報を格納するマップ
	std::unordered_map<GeometryInstanceType, GeometryInstanceActorInfo> mGeometryInstanceActorInfoMap;
};

