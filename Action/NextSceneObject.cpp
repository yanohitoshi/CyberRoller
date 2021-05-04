#include "NextSceneObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "CrystalEffectManager.h"


NextSceneObject::NextSceneObject(const Vector3& _pos, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, Angle(15.0f)
	, MoveSpeed(50.0f)
{

	//GameObjectメンバ変数の初期化
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
	firstPos = _pos;
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
	AABB aabb = { Vector3(-1.0f,-1.0f,-1.0f),Vector3(1.0f,1.0f,3.0f) };
	boxCollider->SetObjectBox(aabb);
	// 4色のエフェクトを付与
	new CrystalEffectManager(this,CrystalColor::WHITE);
	new CrystalEffectManager(this, CrystalColor::RED);
	new CrystalEffectManager(this, CrystalColor::BLUE);
	new CrystalEffectManager(this, CrystalColor::GREEN);
}

NextSceneObject::~NextSceneObject()
{

}

void NextSceneObject::UpdateGameObject(float _deltaTime)
{
	if (PlayerObject::GetNextSceneFlag() == true)
	{
		// 速度付与
		velocity.z = MoveSpeed;

		//Z軸を15度回転させる
		float radian = Math::ToRadians(Angle);
		Quaternion rot = this->GetRotation();
		Quaternion inc(Vector3::UnitZ, radian);
		Quaternion target = Quaternion::Concatenate(rot, inc);
		SetRotation(target);

		// ポジションに速度を足す
		position += velocity;
		// ポジションを更新
		SetPosition(position);
		// 定位置まで届いたら描画カット
		if (position.z >= firstPos.z + 3000.0f)
		{
			meshComponent->SetVisible(false);
		}

		// カメラに注視させるのでポジションを渡す
		mainCamera->SetLerpObjectPos(position);
	}


}

void NextSceneObject::OnCollision(const GameObject& _hitObject)
{
}
