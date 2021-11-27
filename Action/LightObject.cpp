//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "LightObject.h"
#include "Mesh.h"
#include <string>
#include "MeshComponent.h"
#include "RenderingObjectManager.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param	右側に添わせるかどうか
*/
LightObject::LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, bool _isRight)
	: GameObject(false, _objectTag)
	, ShiftPositionX(195.0f)
	, ShiftRightPositionY(50.0f)
	, ShiftLeftPositionY(200.0f)
	, ShiftPositionZ(110.0f)
{
	//GameObjectメンバ変数の初期化
	position = _p;
	position.x += ShiftPositionX;
	position.z -= ShiftPositionZ;

	// 右側に寄せるか左側に寄せるか判定を取りポジションをずらす
	if (_isRight)
	{
		position.y += ShiftRightPositionY;
	}
	else
	{
		position.y -= ShiftLeftPositionY;
	}

	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// ジオメトリインスタンスコンポーネントを生成
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Light/model/SM_PowerCells_Floor.gpmesh"), GeometryInstanceType::G_LIGHT,300);
	// ジオメトリインスタンスマネージャークラスに追加
	geometryInstanceComponent->AddGeometryInstanceManager();

	//メッシュ情報取得
	mesh = geometryInstanceComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
LightObject::~LightObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void LightObject::UpdateGameObject(float _deltaTime)
{
}
