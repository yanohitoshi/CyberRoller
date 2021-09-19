#include "MoveEnemyObject.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "MoveEnemyObjectStateIdle.h"
#include "MoveEnemyObjectStateDead.h"
#include "MoveEnemyObjectStateMoving.h"
#include "MoveEnemyObjectStateTurn.h"
#include "BoxCollider.h"

MoveEnemyObject::MoveEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed,const Vector3& _moveDir, float _moveDistance)
	: EnemyObjectBase(_pos, false, _objectTag, _moveSpeed, _moveDir, _moveDistance)
{
	//GameObjectメンバ変数の初期化
	state = Active;
	scale = Vector3(2.0f, 2.0f, 2.0f);
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	forwardVec = Vector3::NegUnitX;
	charaForwardVec = Vector3::NegUnitX;
	SetScale(scale);

	isDeadFlag = false;

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/enemy_robo_model/SK_Dron_01.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/enemy_robo_model/SK_Dron_01.gpskel"));

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------アニメーションを読み込み-----------------//
	// アイドリングアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/enemy_robo_model/Dron_01_Idle.gpanim", true);
	// 死亡時のアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_DEAD)] = RENDERER->GetAnimation("Assets/Model/enemy_robo_model/Dron_01_Dead.gpanim", false);
	// ターンアニメーション
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_TURN)] = RENDERER->GetAnimation("Assets/Model/enemy_robo_model/Dron_01_rotatation_180_L.gpanim", false);
	//// 走りだしアニメーション
	//animTypes[static_cast<unsigned int>(EnemyState::PLAYER_STATE_RUN_START)] = RENDERER->GetAnimation("Assets/Model/robo_model/Idle_To_Sprint_2.gpanim", false);

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = skeltalMeshComponent->GetMesh();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::NORMAL_ENEMY_TAG, GetOnCollisionFunc());
	//enemyBox = mesh->GetBox();
	enemyBox = { Vector3(-10.0f,-10.0f,-50.0f),Vector3(10.0f,10.0f,10.0f) };
	boxCollider->SetObjectBox(enemyBox);

	// stateプールの初期化
	// ※順番に配列に追加していくのでステータスの列挙と合う順番に追加
	statePools.push_back(new MoveEnemyObjectStateIdle);
	statePools.push_back(new MoveEnemyObjectStateDead);
	statePools.push_back(new MoveEnemyObjectStateMoving);
	statePools.push_back(new MoveEnemyObjectStateTurn);

	//anim変数を速度1.0fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);
	// stateの初期化
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;

}

MoveEnemyObject::~MoveEnemyObject()
{
}

void MoveEnemyObject::UpdateGameObject(float _deltaTime)
{

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
}

void MoveEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
}

void MoveEnemyObject::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER)
	{
		isDeadFlag = true;
	}
}