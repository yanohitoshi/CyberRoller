//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveEnemyObject.h"
#include "Renderer.h"
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
MoveEnemyObject::MoveEnemyObject(const Vector3& _pos, const Tag _objectTag, GameObject* _trackingObject, MoveEnemyData _moveEnemyData)
	: EnemyObjectBase(_pos, false, _objectTag, _trackingObject, _moveEnemyData)
{
	//GameObjectメンバ変数の初期化
	state = Active;
	scale = Size;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	forwardVec = Vector3::NegUnitX;
	charaForwardVec = Vector3::NegUnitX;
	SetScale(scale);

	isAttack = false;
	isDeadFlag = false;

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Enemy/EnemyModel/SK_Dron_01.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Enemy/EnemyModel/SK_Dron_01.gpskel"));
	// mesh情報を取得
	mesh = skeltalMeshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

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
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
*/
void MoveEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER)
	{
		isDeadFlag = true;
	}
}