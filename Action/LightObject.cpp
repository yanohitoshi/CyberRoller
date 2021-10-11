//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "LightObject.h"
#include "Mesh.h"
#include <string>
#include "MeshComponent.h"
#include "Renderer.h"

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
	//geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/groundModel/normalGround.gpmesh"), GeometryInstanceType::gGround);
	//geometryInstanceComponent->AddGeometryInstanceManager();


	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/LightObject/PowerCells/SM_PowerCells_Floor.gpmesh"));
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
LightObject::~LightObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void LightObject::UpdateGameObject(float _deltaTime)
{
}
