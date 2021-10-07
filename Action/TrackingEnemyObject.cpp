//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TrackingEnemyObject.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectStateRespawn.h"
#include "EnemyObjectStateDead.h"
#include "TrackingEnemyStateIdle.h"
#include "TrackingEnemyStateTracking.h"
#include "TrackingEnemyStateMoving.h"
#include "TrackingEnemyStateTurn.h"
#include "TrackingEnemyStateReposition.h"
#include "TrackingEnemyStateAttack.h"
#include "BoxCollider.h"
#include "PlayerTrackingArea.h"
#include "TrackingEnemyAttackArea.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクト判別用tag
@param	移動速度
@param	追跡するオブジェクトのポインタ
@param	追跡エリアの値
*/
TrackingEnemyObject::TrackingEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject, float _areaValue)
	: EnemyObjectBase(_pos, false, _objectTag, _moveSpeed, _trackingObject)
	, Angle(180.0f)
{
	//GameObjectメンバ変数の初期化
	state = Active;
	scale = Size;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	forwardVec = Vector3::NegUnitX;
	charaForwardVec = Vector3::NegUnitX;
	SetScale(scale);

	isTracking = false;
	isDeadFlag = false;
	isAttack = false;
	isPushBackToPlayer = true;

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Enemy/EnemyModel/SK_Dron_01_Tracking.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Enemy/EnemyModel/SK_Dron_01.gpskel"));

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------アニメーションを読み込み-----------------//
	// アイドリングアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Idle.gpanim", true);
	// 死亡時のアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_DEAD)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Dead.gpanim", false);
	// ターンアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_TURN)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_rotatation_180_L.gpanim", false);
	// 攻撃アニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_ATTACK)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Attack.gpanim", false);

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::ENEMY_TAG, GetOnCollisionFunc());
	enemyBox = { BoxMin,BoxMax };
	boxCollider->SetObjectBox(enemyBox);


	// stateプールの初期化
	// ※順番に配列に追加していくのでステータスの列挙と合う順番に追加
	statePools.push_back(new TrackingEnemyStateIdle);
	statePools.push_back(new EnemyObjectStateDead);
	statePools.push_back(new EnemyObjectStateRespawn);
	statePools.push_back(new TrackingEnemyStateAttack);
	statePools.push_back(new TrackingEnemyStateMoving);
	statePools.push_back(new TrackingEnemyStateTurn);
	statePools.push_back(new TrackingEnemyStateTracking);
	statePools.push_back(new TrackingEnemyStateReposition);

	//anim変数を速度1.0fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);
	// stateの初期化
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;

	new PlayerTrackingArea(Tag::PLAYER_TRACKING_AREA, this, _areaValue);
	new TrackingEnemyAttackArea(Tag::PLAYER_TRACKING_AREA, this);

	//Z軸を180度回転させる
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TrackingEnemyObject::~TrackingEnemyObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TrackingEnemyObject::UpdateGameObject(float _deltaTime)
{
	// AABBを更新
	aabb = boxCollider->GetWorldBox();

	if (isAttack && !isDeadFlag)
	{
		nextState = EnemyState::ENEMY_STATE_ATTACK;
	}

	if (isDeadFlag)
	{
		nextState = EnemyState::ENEMY_STATE_DEAD;
	}

	// ステート外部からステート変更があったか？
	if (nowState != nextState)
	{
		statePools[static_cast<unsigned int>(nextState)]->Enter(this, _deltaTime);
		nowState = nextState;
		return;
	}

	// ステート実行
	nextState = statePools[static_cast<unsigned int>(nowState)]->Update(this, _deltaTime);

	// ステート内部からステート変更あったか？
	if (nowState != nextState)
	{
		statePools[static_cast<unsigned int>(nextState)]->Enter(this, _deltaTime);
		nowState = nextState;
	}

	isTracking = false;
	forwardVec = charaForwardVec;
}

/*
@fn めり込み判定
@param	自分のAABB
@param	相手のAABB
*/
void TrackingEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
	// 仮速度変数
	Vector3 ment = Vector3::Zero;

	CalcCollisionFixVec(myAABB, pairAABB, ment);

	// 押し戻し計算を考慮しポジションを更新
	SetPosition(position + ment);
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void TrackingEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ジャンプアタックプレイヤーだったら
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER)
	{
		// 死亡フラグをtrueに
		isDeadFlag = true;
	}

	// 他の敵またはグラウンドと当たったら
	if (_hitObject.GetTag() == Tag::ENEMY || _hitObject.GetTag() == Tag::GROUND)
	{
		// 押し戻し
		FixCollision(aabb, _hitObject.GetAabb());
	}
}
