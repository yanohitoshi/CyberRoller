#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <unordered_map>
#include "GameObject.h"

/*
@enum GeometryInstanceType
	ジオメトリインスタンスメッシュの種類
*/
enum class GeometryInstanceType
{
	G_GROUND,
	G_LIGHT,
	G_NEEDLE,
	G_NEEDLE_PANEL,
	G_JUMP_SWITCH,
	G_BASE_SWITCH,
	G_MOVE_WALL,
};

/*
@file GeometryInstanceManager.h
@brief ジオメトリインスタンスメッシュの管理と描画を行うクラス
*/
class GeometryInstanceManager
{
public:

	/*
	@fn コンストラクタ
	*/
	GeometryInstanceManager() {};

	/*
	@fn デストラクタ
	*/
	~GeometryInstanceManager();

	/*
	@fn インスタンス用のメッシュを設定する
	@param _mesh 登録するメッシュ
	@param _maxInstanceNum 最大インスタンス数
	@param _type ジオメトリインスタンスの種類
	*/
	void SetInstanceMesh(class Mesh* _mesh, const unsigned int _maxInstanceNum, const GeometryInstanceType _type);

	/*
	@fn 行列バッファの更新
	*/
	void PrepareModelMatrice();

	/*
	@fn 描画処理
	@param _shader 描画するシェーダー
	*/
	void Draw(class Shader* _shader);

	/*
	@fn ジオメトリインスタンス用のオブジェクトを追加
	@param _gameObject 追加するオブジェクト
	@param _type 追加するオブジェクトのジオメトリインスタンスの種類
	*/
	void AddGeometryInstanceGameObject(class GameObject* _gameObject, GeometryInstanceType _type);

	/*
	@fn ジオメトリインスタンス用のオブジェクトを削除
	@param _gameObject 削除するオブジェクト
	@param _type 削除するオブジェクトのジオメトリインスタンスの種類
	*/
	void RemoveGeometryInstanceGameObject(class GameObject* _gameObject, GeometryInstanceType _type);

	/*
	@fn ジオメトリインスタンスの種類に応じてメッシュを返す
	@param _type ジオメトリインスタンスの種類
	*/
	class Mesh* GetMesh(GeometryInstanceType _type) { return geometryInstanceGameObjectInfoMap[_type].mesh; }

	/*
	@fn ジオメトリインスタンスのアクターを格納するマップをクリア
	*/
	void ClearGeometryInstanceGameObjectMap();

private:

	/*
	@struct ジオメトリインスタンスのアクター情報の構造体
	*/
	struct GeometryInstanceActorInfo
	{
		// インスタンス最大数​
		unsigned int maxInstanceNum;
		// インデックスバッファにあるインデックスの数
		unsigned int numIndices;
		//頂点配列オブジェクトのOpenGL ID
		unsigned int vertexArray;
		//行列バッファ
		float* modelMatrice;
		//インスタンス描画可能なID
		unsigned int instanceVAO;
		//メッシュのポインタ
		class Mesh* mesh;

	};

	/*
	@fn シェーダーにテクスチャをセット
	@param _shader シェーダー
	@param _type ジオメトリインスタンスの種類
	*/
	void SetTextureToShader(Shader* _shader, GeometryInstanceType _type);

	//ジオメトリインスタンスのオブジェクトを格納するマップ
	std::unordered_map<GeometryInstanceType, std::vector<GameObject*>> geometryInstanceGameObjectMap;
	//ジオメトリインスタンスのオブジェクト情報を格納するマップ
	std::unordered_map<GeometryInstanceType, GeometryInstanceActorInfo> geometryInstanceGameObjectInfoMap;
};