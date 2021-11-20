//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "NeedleObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	親となるobjectのポインタ
@param	親objectとの間隔
@param	objectのサイズ
@param	オブジェクト判別用tag
*/
NeedleObject::NeedleObject(GameObject* _owner ,const Vector3& _offset, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	position = _owner->GetPosition() + _offset;
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	owner = _owner;
	// ジオメトリインスタンスコンポーネントを生成
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/Needle/model/needles.gpmesh"), GeometryInstanceType::G_NEEDLE,300);
	// ジオメトリインスタンスマネージャークラスに追加
	geometryInstanceComponent->AddGeometryInstanceManager();
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
NeedleObject::~NeedleObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void NeedleObject::UpdateGameObject(float _deltaTime)
{
	// ownerの速度を付与
	velocity = owner->GetVelocity();

	// ポジションに速度を足す
	position = position + velocity * _deltaTime;

	// ポジションを更新
	SetPosition(position);
}
