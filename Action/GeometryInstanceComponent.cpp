//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GeometryInstanceComponent.h"
#include "RenderingObjectManager.h"
#include "Game.h"

/*
@fn コンストラクタ
@brief メンバー変数の初期化とジオメトリインスタンスマネージャーにメッシュを登録
@param _owner このコンポーネントの所有オブジェクト
@param _mesh 登録したいメッシュ
@param _type ジオメトリインスタンスの種類
@param _maxInstanceNum 最大描画数
*/
GeometryInstanceComponent::GeometryInstanceComponent(GameObject* _owner, Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum)
	:Component(_owner)
	, geometryInstanceManager(RENDERING_OBJECT_MANAGER->GetGeometryInstanceManager())
	, geometryInstanceType(_type)
	, mesh(_mesh)

{
	//ジオメトリインスタンスマネージャーにメッシュを登録
	geometryInstanceManager->SetInstanceMesh(_mesh, _maxInstanceNum, _type);
}

/*
@brief ジオメトリインスタンスマネージャーにアクターに描画可能なアクターを追加
*/
void GeometryInstanceComponent::AddGeometryInstanceManager()
{
	//ジオメトリインスタンスマネージャーに描画するアクターを追加
	geometryInstanceManager->AddGeometryInstanceGameObject(GetOwner(), geometryInstanceType);
}

/*
@brief ジオメトリインスタンスマネージャーからアクターを削除
*/
void GeometryInstanceComponent::RemoveGeometryInstanceManager()
{
	// ジオメトリインスタンスマネージャーからアクターを削除
	geometryInstanceManager->RemoveGeometryInstanceGameObject(GetOwner(), geometryInstanceType);
}

/*
@brief ジオメトリインスタンスマネージャーからメッシュのポインタを返す
@return メッシュのポインタ
*/
Mesh* GeometryInstanceComponent::GetMesh() const
{
	//ジオメトリインスタンスマネージャーからメッシュを返す
	return geometryInstanceManager->GetMesh(geometryInstanceType);
}