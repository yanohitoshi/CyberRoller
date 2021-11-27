//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveEnemyObject.h"
#include "RenderingObjectManager.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectStateRespawn.h"
#include "EnemyObjectStateDead.h"
#include "EnemyObjectStateAttack.h"
#include "MoveEnemyObjectStateIdle.h"
#include "MoveEnemyObjectStateMoving.h"
#include "MoveEnemyObjectStateTurn.h"
#include "EnemyAttackArea.h"
#include "BoxCollider.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクト判別用tag
@param	追跡対象のオブyジェクトのポインタ
@param	左右に移動する敵が固有で持つデータ構造体
*/
MoveEnemyObject::MoveEnemyObject(const Vector3& _pos, const Tag _objectTag, MoveEnemyData _moveEnemyData)
	: EnemyObjectBase(_pos, false, _objectTag, _moveEnemyData)
{
	//GameObjectメンバ変数の初期化
	state = Active;
	scale = Size;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	forwardVec = Vector3::NegUnitX;
	charaForwardVec = Vector3::NegUnitX;
	SetScale(scale);

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERING_OBJECT_MANAGER->GetMesh("Assets/Model/Enemy/model/SK_Dron_01.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERING_OBJECT_MANAGER->GetSkeleton("Assets/Model/Enemy/model/SK_Dron_01.gpskel"));
	// mesh情報を取得
	mesh = skeltalMeshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------アニメーションを読み込み-----------------//
	// アイドリングアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERING_OBJECT_MANAGER->GetAnimation("Assets/Model/Enemy/animation/Dron_01_Idle.gpanim", true);
	// 死亡時のアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_DEAD)] = RENDERING_OBJECT_MANAGER->GetAnimation("Assets/Model/Enemy/animation/Dron_01_Dead.gpanim", false);
	// ターンアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_TURN)] = RENDERING_OBJECT_MANAGER->GetAnimation("Assets/Model/Enemy/animation/Dron_01_rotatation_180_L.gpanim", false);
	// 攻撃アニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_ATTACK)] = RENDERING_OBJECT_MANAGER->GetAnimation("Assets/Model/Enemy/animation/Dron_01_Attack.gpanim", false);
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::ENEMY_TAG, GetOnCollisionFunc());
	enemyBox = { BoxMin,BoxMax };
	boxCollider->SetObjectBox(enemyBox);

	// stateをstatePool用マップに追加
	AddStatePoolMap(new MoveEnemyObjectStateIdle, EnemyState::ENEMY_STATE_IDLE);
	AddStatePoolMap(new EnemyObjectStateDead, EnemyState::ENEMY_STATE_DEAD);
	AddStatePoolMap(new EnemyObjectStateRespawn, EnemyState::ENEMY_STATE_RESPAWN);
	AddStatePoolMap(new EnemyObjectStateAttack, EnemyState::ENEMY_STATE_ATTACK);
	AddStatePoolMap(new MoveEnemyObjectStateMoving, EnemyState::ENEMY_STATE_MOVING);
	AddStatePoolMap(new MoveEnemyObjectStateTurn, EnemyState::ENEMY_STATE_TURN);

	//anim変数を速度1.0fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);
	// stateの初期化
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;

	// 攻撃エリアを追加
	new EnemyAttackArea(Tag::PLAYER_TRACKING_AREA, this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
MoveEnemyObject::~MoveEnemyObject()
{
	// Mapの後片付け
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_IDLE);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_DEAD);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_RESPAWN);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_ATTACK);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_MOVING);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_TURN);
	ClearStatePoolMap();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void MoveEnemyObject::UpdateGameObject(float _deltaTime)
{
	if (isAttack && !isDead)
	{
		nextState = EnemyState::ENEMY_STATE_ATTACK;
	}

	if (isDead)
	{
		nextState = EnemyState::ENEMY_STATE_DEAD;
	}

	// ステート外部からステート変更があったか？
	if (nowState != nextState)
	{
		//マップの中に追加するアクターのコンテナがあるかどうかを調べる
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// ステート実行
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		nextState = statePoolMap[nowState]->Update(this, _deltaTime);
	}

	// ステート内部からステート変更あったか？
	if (nowState != nextState)
	{
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}
		nowState = nextState;
	}


	isAttack = false;
}

/*
@fn めり込み判定
@param	自分のAABB
@param	相手のAABB
*/
void MoveEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
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
*/
void MoveEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ジャンプアタックプレイヤーまたは爆発に当たったら
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER || _physicsTag == PhysicsTag::EXPLOSION_AREA_TAG)
	{
		// 死亡状態にする
		isDead = true;
		defeatedObjectPosition = _hitObject.GetPosition();
	}

	// 当たった相手が押し戻す相手か判定
	bool isPushBack = _physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
		_physicsTag == PhysicsTag::WALL_TAG || _physicsTag == PhysicsTag::SWITCH_BASE_TAG ||
		_physicsTag == PhysicsTag::SWITCH_TAG;

	// 当たった相手が押し戻す相手だったら
	if (isPushBack)
	{
		aabb = boxCollider->GetWorldBox();
		// 押し戻し
		FixCollision(aabb, _hitObject.GetAabb());
	}
}