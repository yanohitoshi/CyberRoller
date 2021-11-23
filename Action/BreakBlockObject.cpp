#include "BreakBlockObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "BreakBlockObjectEffectManager.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
*/
BreakBlockObject::BreakBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, CorrectionAabbValue(0.1f)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	isPushBackToPlayer = true;
	isCheckGroundToPlayer = true;
	isPushBackToCamera = true;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/Ground/model/breakGround.gpmesh"));
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::BREAK_GROUND_TAG, GetOnCollisionFunc());
	aabb = mesh->GetBox();

	//プレイヤーがすり抜けないようにAABBのサイズを補正
	aabb.max.y += CorrectionAabbValue;
	aabb.min.y -= CorrectionAabbValue;
	boxCollider->SetObjectBox(aabb);

	new BreakBlockObjectEffectManager(this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
BreakBlockObject::~BreakBlockObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void BreakBlockObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void BreakBlockObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// 爆発エリアに入ったら
	if (_physicsTag == PhysicsTag::EXPLOSION_AREA_TAG)
	{
		// 描画を切る
		meshComponent->SetVisible(false);
		// ステータスを無効化状態にする
		SetState(State::Disabling);
	}
}
