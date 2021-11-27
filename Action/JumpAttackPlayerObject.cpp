//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "JumpAttackPlayerObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "JumpAttackEffectManager.h"
#include "PlayerAttackHitEffectManager.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクトのサイズ
@param	オブジェクト判別用tag
*/
JumpAttackPlayerObject::JumpAttackPlayerObject(PlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag)
	: GameObject(false, _objectTag)
	, Rotation(10.0f)
	, ShiftPositionZ(100.0f)
{
	// 変数初期化
	ownerObject = _ownerObject;
	position = ownerObject->GetPosition();
	position.z += ShiftPositionZ;
	rotationAngle = 0.0f;
	isHIt = false;
	// 前方ベクトル初期化
	forwardVec = ownerObject->GetForwardVec();

	SetPosition(position);
	SetScale(_size);
	SetState(State::Disabling);

	// メッシュ読み込み
	meshComponent = new MeshComponent(this, false, false);
	meshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Player/JumpAttackPlayerModel/JumpAttackPlayer.gpmesh"));
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//攻撃判定用のsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::JUMP_ATTACK_PLAYER_TAG, GetOnCollisionFunc());
	Sphere jumpAttackSphere = { Vector3(0.0f,0.0f,0.0f),5.0f };
	sphereCollider->SetObjectSphere(jumpAttackSphere);

	// ジャンプアタック中のエフェクトを管理するクラスを生成
	new JumpAttackEffectManager(this);
	// ヒットエフェクトを管理するクラスを生成
	new PlayerAttackHitEffectManager(ownerObject);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
JumpAttackPlayerObject::~JumpAttackPlayerObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void JumpAttackPlayerObject::UpdateGameObject(float _deltaTime)
{
	// オーナーがジャンプアタック状態だったら
	if (ownerObject->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
	{
		// 自分のステータスをActiveにセット
		SetState(State::Active);
		// 描画On
		meshComponent->SetVisible(true);
	}
	else
	{
		// 自分のステータスをDisablingにセット
		SetState(State::Disabling);
		// 描画Off
		meshComponent->SetVisible(false);
		// ヒットフラグ初期化
		isHIt = false;
	}

	// 自分がActiveで何にもヒットしていなかったら
	if (state == State::Active && !isHIt)
	{
		// 回転処理
		rotationAngle += Rotation;
		//Z軸を指定角度回転させる
		float radian = Math::ToRadians(rotationAngle);
		Quaternion rot = this->GetRotation();
		Quaternion inc(Vector3::UnitY, radian);
		Quaternion target = Quaternion::Concatenate(rot, inc);
		SetRotation(target);
	}

	// ポジション更新
	position = ownerObject->GetPosition();
	position.z += ShiftPositionZ;
	SetPosition(position);
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void JumpAttackPlayerObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	bool isHitTarget = _hitObject.GetTag() == Tag::ENEMY || _physicsTag == PhysicsTag::SWITCH_TAG ||
		_physicsTag == PhysicsTag::BOMB_TAG;
	// 追跡対象に当たったら
	if (isHitTarget)
	{
		// ヒットフラグをtrueに
		isHIt = true;
		// ジャンプアタック成功状態にする
		ownerObject->SetIsJumpAttackSuccess(true);
	}
}