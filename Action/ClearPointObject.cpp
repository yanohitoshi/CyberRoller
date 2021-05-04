#include "ClearPointObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "GameClearEffectManeger.h"
#include "CrystalEffectManager.h"

ClearPointObject::ClearPointObject(const Vector3& _pos, const Tag& _objectTag)
	: GameObject(false,_objectTag)
	, Angle(10.0f)
	, MoveSpeed(50.0f)
{

	//GameObjectメンバ変数の初期化
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
	tag = _objectTag;
	state = Active;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/goods_model/SM_Gems_01a.gpmesh"));
	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::ClearPointTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	new GameClearEffectManeger(this);

	// 4色のエフェクトを付与
	new CrystalEffectManager(this, CrystalColor::WHITE);
	new CrystalEffectManager(this, CrystalColor::RED);
	new CrystalEffectManager(this, CrystalColor::BLUE);
	new CrystalEffectManager(this, CrystalColor::GREEN);


}

ClearPointObject::~ClearPointObject()
{

}

void ClearPointObject::UpdateGameObject(float _deltaTime)
{
	if (PlayerObject::GetClearFlag() == true)
	{
		// 速度を付与
		velocity.z = MoveSpeed;

		//Z軸を10度回転させる
		float radian = Math::ToRadians(Angle);
		Quaternion rot = this->GetRotation();
		Quaternion inc(Vector3::UnitZ, radian);
		Quaternion target = Quaternion::Concatenate(rot, inc);
		SetRotation(target);

		// ポジションに速度を足す
		position += velocity;
		// ポジションを更新
		SetPosition(position);
		// カメラに注視させるのでポジションを渡す
		mainCamera->SetLerpObjectPos(position);

	}
}

void ClearPointObject::OnCollision(const GameObject& _hitObject)
{
}

