//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObject.h"
#include "RenderingObjectManager.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "SoundEffectComponent.h"
#include "BoxCollider.h"
#include "ExplosionObjectStateBase.h"
#include "ExplosionObjectStateIdle.h"
#include "ExplosionObjectStateStartExplosion.h"
#include "ExplosionObjectStateExplosion.h"
#include "ExplosionObjectStateRespawn.h"
#include "ExplosionObjectEffectManager.h"
#include "ExplosionArea.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクト判別用tag
*/
ExplosionObject::ExplosionObject(const Vector3& _pos, const Tag _objectTag)
	: ExplosionObjectBase(_objectTag)
	, ShiftPositionZ(100.0f)
{
	//GameObjectメンバ変数の初期化
	velocity.Zero;

	position = _pos;
	position.z += ShiftPositionZ;
	SetPosition(position);
	// 初期ポジションを保存
	firstPosition = position;

	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isStartExplosion = false;
	isHitJumpAttackPlayer = false;
	isHitExplosionObject = false;
	hitPosition = Vector3(0.0f,0.0f,0.0f);

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Bomb/model/bomb.gpmesh"));
	meshComponent->SetEmissiveColor(Color::LightBlue);

	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::BOMB_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-100.0f,-100.0f,-100.0f),Vector3(100.0f,100.0f,100.0f) };
	boxCollider->SetObjectBox(aabb);

	// ステートマップにstateクラスを追加
	AddStatePoolMap(new ExplosionObjectStateIdle(), ExplosionObjectState::IDLE);
	AddStatePoolMap(new ExplosionObjectStateStartExplosion(this), ExplosionObjectState::EXPLOSION_START);
	AddStatePoolMap(new ExplosionObjectStateExplosion(this), ExplosionObjectState::EXPLOSION);
	AddStatePoolMap(new ExplosionObjectStateRespawn(), ExplosionObjectState::RESPAWN);

	nowState = ExplosionObjectState::NUM;
	nextState = ExplosionObjectState::IDLE;

	new ExplosionObjectEffectManager(this);
	new ExplosionArea(Tag::EXPLOSION_AREA,this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ExplosionObject::~ExplosionObject()
{
	// Mapの後片付け
	RemoveStatePoolMap(ExplosionObjectState::IDLE);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION_START);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION);
	RemoveStatePoolMap(ExplosionObjectState::RESPAWN);
	ClearStatePoolMap();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ExplosionObject::UpdateGameObject(float _deltaTime)
{
	if (isStartExplosion && !isExplode && nowState != ExplosionObjectState::EXPLOSION_START)
	{
		nextState = ExplosionObjectState::EXPLOSION_START;
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
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void ExplosionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// アイドリング状態中にジャンプアタックプレイヤーと当たったら
	if (_physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG && nowState == ExplosionObjectState::IDLE)
	{
		isStartExplosion = true;
		isHitJumpAttackPlayer = true;
		hitPosition = _hitObject.GetPosition();
	}

	// アイドリング状態中にジャンプアタックプレイヤーと当たったら
	bool isHitUnMoveExplosionObject = _physicsTag == PhysicsTag::PLAYER_TAG && nowState == ExplosionObjectState::IDLE ||
		_physicsTag == PhysicsTag::ENEMY_TAG && nowState == ExplosionObjectState::IDLE;
	if(isHitUnMoveExplosionObject)
	{
		isStartExplosion = true;
		isHitJumpAttackPlayer = false;
		hitPosition = Vector3::Zero;
	}

	// 爆発開始中の時
	if (nowState == ExplosionObjectState::EXPLOSION_START)
	{
		// 即爆発するオブジェクトに当たったら
		bool isImmediateExplosionObject = _physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
			_physicsTag == PhysicsTag::BREAK_GROUND_TAG || _physicsTag == PhysicsTag::ENEMY_TAG;

		if (isImmediateExplosionObject)
		{
			isHitExplosionObject = true;
		}
	}
}