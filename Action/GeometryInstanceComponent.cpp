#include "GeometryInstanceComponent.h"
#include "Renderer.h"
#include "Game.h"

/// <summary>
/// メンバー変数の初期化とジオメトリインスタンスマネージャーにメッシュを登録
/// </summary>
/// <param name="_owner">このコンポーネントの所有アクター</param>
/// <param name="_mesh">登録したいメッシュ</param>
/// <param name="_type">ジオメトリインスタンスの種類</param>
/// <param name="_maxInstanceNum">最大描画数</param>
GeometryInstanceComponent::GeometryInstanceComponent(GameObject* _owner, Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum)
	:Component(_owner)
	,mGeometryInstanceManager(RENDERER->GetGeometryInstanceManager())
	,mGeometryInstanceType(_type)
	,mMesh(_mesh)

{
	//ジオメトリインスタンスマネージャーにメッシュを登録
	mGeometryInstanceManager->SetInstanceMesh(_mesh, _maxInstanceNum, _type);
}

void GeometryInstanceComponent::AddGeometryInstanceManager()
{
	//ジオメトリインスタンスマネージャーに描画するアクターを追加
	mGeometryInstanceManager->AddGeometryInstanceActor(GetOwner(), mGeometryInstanceType);
}

void GeometryInstanceComponent::RemoveGeometryInstanceManager()
{
	//ジオメトリインスタンスマネージャーからアクターを削除
	//mGeometryInstanceManager->RemoveGeometryInstanceActor(GetOwner(), mGeometryInstanceType);
	////ゲームの状態が終了でないなら
	//if (Game::GetState() != GameState::EQuit)
	//{
	//}
}

Mesh* GeometryInstanceComponent::GetMesh() const
{
	//ジオメトリインスタンスマネージャーからメッシュを返す
	return mGeometryInstanceManager->GetMesh(mGeometryInstanceType);
}
