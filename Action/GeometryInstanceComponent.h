#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include <string>
#include "GeometryInstanceManager.h"

/*
@file GeometryInstanceComponent.h
@brief ジオメトリインスタンスのためのコンポーネント
*/
class GeometryInstanceComponent : public Component
{
public:

	/*
	@fn コンストラクタ
	@brief メンバー変数の初期化とジオメトリインスタンスマネージャーにメッシュを登録
	@param _owner このコンポーネントの所有オブジェクト
	@param _mesh 登録したいメッシュ
	@param _type ジオメトリインスタンスの種類
	@param _maxInstanceNum 最大描画数
	*/
	GeometryInstanceComponent(class GameObject* _owner,class Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum = 200);

	/*
	@brief ジオメトリインスタンスマネージャーにアクターに描画可能なアクターを追加
	*/
	void AddGeometryInstanceManager();

	/*
	@brief ジオメトリインスタンスマネージャーからアクターを削除
	*/
	void RemoveGeometryInstanceManager();

	/*
	@brief ジオメトリインスタンスマネージャーからメッシュのポインタを返す
	@return メッシュのポインタ
	*/
	class Mesh* GetMesh()const;

private:

	//ジオメトリインスタンスマネージャーのポインタ
	class GeometryInstanceManager* geometryInstanceManager;
	//ジオメトリインスタンスの種類
	GeometryInstanceType geometryInstanceType;
	//メッシュのポインタ
	class Mesh* mesh;
};

