#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include <string>
#include "GeometryInstanceManager.h"

/// <summary>
/// ジオメトリインスタンスのためのコンポーネント
/// </summary>
class GeometryInstanceComponent : public Component
{
public:
	/// <summary>
	/// メンバー変数の初期化とジオメトリインスタンスマネージャーにメッシュを登録
	/// </summary>
	/// <param name="_owner">このコンポーネントの所有アクター</param>
	/// <param name="_mesh">登録したいメッシュ</param>
	/// <param name="_type">ジオメトリインスタンスの種類</param>
	/// <param name="_maxInstanceNum">最大描画数</param>
	GeometryInstanceComponent(class GameObject* _owner,class Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum = 200);

	/// <summary>
	/// ジオメトリインスタンスマネージャーにアクターに描画可能なアクターを追加
	/// </summary>
	void AddGeometryInstanceManager();

	/// <summary>
	/// ジオメトリインスタンスマネージャーからアクターを削除
	/// </summary>
	void RemoveGeometryInstanceManager();

	/// <summary>
	/// ジオメトリインスタンスマネージャーからメッシュのポインタを返す
	/// </summary>
	/// <returns>メッシュのポインタ</returns>
	class Mesh* GetMesh()const;

private:
	//ジオメトリインスタンスマネージャーのポインタ
	class GeometryInstanceManager* mGeometryInstanceManager;
	//ジオメトリインスタンスの種類
	GeometryInstanceType mGeometryInstanceType;
	//メッシュのポインタ
	class Mesh* mMesh;
};

