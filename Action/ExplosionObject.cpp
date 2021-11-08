#include "ExplosionObject.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "ExplosionObjectStateBase.h"
#include "ExplosionObjectStateIdle.h"
#include "ExplosionObjectStateStartExplosion.h"
#include "ExplosionObjectStateExplosion.h"
#include "ExplosionObjectStateRespawn.h"
#include "ExplosionObjectEffectManager.h"
#include "ExplosionArea.h"

ExplosionObject::ExplosionObject(const Vector3& _pos, const Tag _objectTag)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	velocity.Zero;
	position = _pos;
	position.z += 100.0f;
	SetPosition(position);
	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isStartExplosion = false;
	isHitJumpAttackPlayer = false;
	isHitExplosionObject = false;
	hitPosition = Vector3(0.0f,0.0f,0.0f);
	// 初期ポジションを保存
	firstPosition = position;
	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/bombObject/bomb.gpmesh"));
	meshComponent->SetEmissiveColor(Color::LightBlue);

	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::BOMB_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-100.0f,-100.0f,-100.0f),Vector3(100.0f,100.0f,100.0f) };
	boxCollider->SetObjectBox(aabb);

	AddStatePoolMap(new ExplosionObjectStateIdle(), ExplosionObjectState::IDLE);
	AddStatePoolMap(new ExplosionObjectStateStartExplosion(), ExplosionObjectState::EXPLOSION_START);
	AddStatePoolMap(new ExplosionObjectStateExplosion(), ExplosionObjectState::EXPLOSION);
	AddStatePoolMap(new ExplosionObjectStateRespawn(), ExplosionObjectState::RESPAWN);

	nowState = ExplosionObjectState::NUM;
	nextState = ExplosionObjectState::IDLE;

	new ExplosionObjectEffectManager(this);
	new ExplosionArea(Tag::EXPLOSION_AREA,this);
}

ExplosionObject::~ExplosionObject()
{
	RemoveStatePoolMap(ExplosionObjectState::IDLE);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION_START);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION);
	RemoveStatePoolMap(ExplosionObjectState::RESPAWN);
	ClearStatePoolMap();
}

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

void ExplosionObject::AddStatePoolMap(ExplosionObjectStateBase* _state, ExplosionObjectState _stateTag)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto stateMaps = statePoolMap.find(_stateTag);

	//あるとき
	if (stateMaps != statePoolMap.end())
	{
		return;
	}
	else //ないとき
	{
		statePoolMap[_stateTag] = _state;
	}
}

void ExplosionObject::RemoveStatePoolMap(ExplosionObjectState _stateTag)
{
	delete statePoolMap[_stateTag];
}

void ExplosionObject::ClearStatePoolMap()
{
	statePoolMap.clear();
}

void ExplosionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{

	if (_physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG && nowState == ExplosionObjectState::IDLE)
	{
		isStartExplosion = true;
		isHitJumpAttackPlayer = true;
		hitPosition = _hitObject.GetPosition();
	}
	
	if(_physicsTag == PhysicsTag::PLAYER_TAG && nowState == ExplosionObjectState::IDLE)
	{
		isStartExplosion = true;
		isHitJumpAttackPlayer = false;
		hitPosition = Vector3::Zero;
	}

	if (nowState == ExplosionObjectState::EXPLOSION_START)
	{
		if (_physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
			_physicsTag == PhysicsTag::BREAK_GROUND_TAG || _physicsTag == PhysicsTag::ENEMY_TAG)
		{
			isHitExplosionObject = true;
		}
	}
}
