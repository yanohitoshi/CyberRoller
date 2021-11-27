//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "NormalEnemyObject.h"
#include "RenderingObjectManager.h"
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
NormalEnemyObject::NormalEnemyObject(const Vector3& _pos, const Tag _objectTag)
	: EnemyObjectBase(_pos, false , _objectTag)
	, Angle(180.0f)
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
	skeltalMeshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Enemy/model/SK_Dron_01.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERING_OBJECT_MANAGER->CreateSkeleton("Assets/Model/Enemy/model/SK_Dron_01.gpskel"));
	// mesh情報を取得
	mesh = skeltalMeshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------アニメーションを読み込み-----------------//
	// アイドリングアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Enemy/animation/Dron_01_Idle.gpanim", true);
	// 死亡時のアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_DEAD)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Enemy/animation/Dron_01_Dead.gpanim", false);
	// 攻撃アニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_ATTACK)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Enemy/animation/Dron_01_Attack.gpanim", false);
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::ENEMY_TAG, GetOnCollisionFunc());
	enemyBox = { BoxMin,BoxMax };
	boxCollider->SetObjectBox(enemyBox);

	// stateをstatePool用マップに追加
	AddStatePoolMap(new NormalEnemyObjectStateIdle, EnemyState::ENEMY_STATE_IDLE);
	AddStatePoolMap(new EnemyObjectStateDead, EnemyState::ENEMY_STATE_DEAD);
	AddStatePoolMap(new EnemyObjectStateRespawn, EnemyState::ENEMY_STATE_RESPAWN);
	AddStatePoolMap(new EnemyObjectStateAttack, EnemyState::ENEMY_STATE_ATTACK);

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
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_IDLE);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_DEAD);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_RESPAWN);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_ATTACK);
	ClearStatePoolMap();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void NormalEnemyObject::UpdateGameObject(float _deltaTime)
{
	
	if (isAttack && !isDead)
	{
		nextState = EnemyState::ENEMY_STATE_ATTACK;
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
void NormalEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER || _physicsTag == PhysicsTag::EXPLOSION_AREA_TAG)
	{
		isDead = true;
		defeatedObjectPosition = _hitObject.GetPosition();
	}

	bool isPushBack = _physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
		_physicsTag == PhysicsTag::WALL_TAG || _physicsTag == PhysicsTag::SWITCH_BASE_TAG ||
		_physicsTag == PhysicsTag::SWITCH_TAG;

	if (isPushBack)
	{
		aabb = boxCollider->GetWorldBox();
		// 押し戻し
		FixCollision(aabb, _hitObject.GetAabb());
	}
}

/*
@fn めり込み判定
@param	自分のAABB
@param	相手のAABB
*/
void NormalEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
	// 仮速度変数
	Vector3 ment = Vector3::Zero;

	CalcCollisionFixVec(myAABB, pairAABB, ment);

	// 押し戻し計算を考慮しポジションを更新
	SetPosition(position + ment);
}