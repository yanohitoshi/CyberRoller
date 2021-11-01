#include "ExplosionObject.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "ExplosionObjectStateBase.h"
#include "ExplosionObjectStateIdle.h"


ExplosionObject::ExplosionObject(const Vector3& _pos, const Tag _objectTag, float _areaValue)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	velocity.Zero;
	position = _pos;
	position.z += 100.0f;
	SetPosition(position);
	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isExplosion = false;
	isHitJumpAttackPlayer = false;
	hitPosition = Vector3(0.0f,0.0f,0.0f);

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/bomb.gpmesh"));

	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::BOMB_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-5.0f,-5.0f,-5.0f),Vector3(5.0f,5.0f,15.0f) };
	boxCollider->SetObjectBox(aabb);

	AddStatePoolMap(new ExplosionObjectStateIdle(), ExplosionObjectState::IDLE);

	nowState = ExplosionObjectState::NONE;
	nextState = ExplosionObjectState::IDLE;
}

ExplosionObject::~ExplosionObject()
{
	RemoveStatePoolMap(ExplosionObjectState::IDLE);
	ClearStatePoolMap();
}

void ExplosionObject::UpdateGameObject(float _deltaTime)
{
	if (isExplosion)
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
	if (_physicsTag == PhysicsTag::PLAYER_TAG || _physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		isExplosion = true;
	}

	if (_physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		isHitJumpAttackPlayer = true;
		hitPosition = _hitObject.GetPosition();
	}
	else if(_physicsTag == PhysicsTag::PLAYER_TAG)
	{
		isHitJumpAttackPlayer = false;
	}
}
