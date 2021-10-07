//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "NormalEnemyObject.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectStateRespawn.h"
#include "EnemyObjectStateDead.h"
#include "EnemyObjectStateAttack.h"
#include "NormalEnemyObjectStateIdle.h"
#include "EnemyAttackArea.h"
#include "BoxCollider.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクト判別用tag
@param	追跡するオブジェクトのポインタ
*/
NormalEnemyObject::NormalEnemyObject(const Vector3& _pos, const Tag _objectTag, GameObject* _trackingObject)
	: EnemyObjectBase(_pos, false , _objectTag, _trackingObject)
	, Angle(180.0f)
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

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------アニメーションを読み込み-----------------//
	// アイドリングアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Idle.gpanim", true);
	// 死亡時のアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_DEAD)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Dead.gpanim", false);
	// 攻撃アニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_ATTACK)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Attack.gpanim", false);
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::ENEMY_TAG, GetOnCollisionFunc());
	enemyBox = { BoxMin,BoxMax };
	boxCollider->SetObjectBox(enemyBox);

	// stateプールの初期化
	// ※順番に配列に追加していくのでステータスの列挙と合う順番に追加
	statePools.push_back(new NormalEnemyObjectStateIdle);
	statePools.push_back(new EnemyObjectStateDead);
	statePools.push_back(new EnemyObjectStateRespawn);
	statePools.push_back(new EnemyObjectStateAttack);
	
	//anim変数を速度1.0fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);

	// stateの初期化
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;

	// 攻撃エリアを追加
	new EnemyAttackArea(Tag::PLAYER_TRACKING_AREA, this);

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
NormalEnemyObject::~NormalEnemyObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void NormalEnemyObject::UpdateGameObject(float _deltaTime)
{
	if (isAttack && !isDeadFlag)
	{
		nextState = EnemyState::ENEMY_STATE_ATTACK;
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

	isAttack = false;
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
*/
void NormalEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER)
	{
		isDeadFlag = true;
	}
}
