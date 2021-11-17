#include "FallExplosionObject.h"
#include "FallExplosionArea.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "ExplosionObjectStateBase.h"
#include "FallExplosionObjectStateIdle.h"
#include "ExplosionObjectStateFall.h"
#include "ExplosionObjectStateExplosion.h"
#include "FallExplosionObjectStateRespawn.h"
#include "ExplosionObjectEffectManager.h"
#include "ExplosionArea.h"

FallExplosionObject::FallExplosionObject(FallExplosionArea* _owner, const Vector3& _pos, const Tag _objectTag)
	: ExplosionObjectBase(_objectTag)
{
	//GameObject�����o�ϐ��̏�����
	velocity.Zero;

	position = _pos;
	SetPosition(position);
	// �����|�W�V������ۑ�
	firstPosition = position;
	fallArea = _owner->GetArea();
	owner = _owner;
	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isStartExplosion = false;
	isHitJumpAttackPlayer = false;
	isHitExplosionObject = false;
	hitPosition = Vector3(0.0f, 0.0f, 0.0f);

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/BombObject/bomb.gpmesh"));
	meshComponent->SetEmissiveColor(Color::LightBlue);

	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::FALL_BOMB_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-100.0f,-100.0f,-100.0f),Vector3(100.0f,100.0f,100.0f) };
	boxCollider->SetObjectBox(aabb);

	AddStatePoolMap(new FallExplosionObjectStateIdle(), ExplosionObjectState::IDLE);
	AddStatePoolMap(new ExplosionObjectStateFall(), ExplosionObjectState::FALL);
	AddStatePoolMap(new ExplosionObjectStateExplosion(), ExplosionObjectState::EXPLOSION);
	AddStatePoolMap(new FallExplosionObjectStateRespawn(), ExplosionObjectState::RESPAWN);

	nowState = ExplosionObjectState::NUM;
	nextState = ExplosionObjectState::RESPAWN;

	new ExplosionObjectEffectManager(this);
	new ExplosionArea(Tag::EXPLOSION_AREA, this);
}

FallExplosionObject::~FallExplosionObject()
{
	RemoveStatePoolMap(ExplosionObjectState::IDLE);
	RemoveStatePoolMap(ExplosionObjectState::FALL);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION);
	RemoveStatePoolMap(ExplosionObjectState::RESPAWN);
	ClearStatePoolMap();
}

void FallExplosionObject::UpdateGameObject(float _deltaTime)
{
	if (owner->GetIsFallStart())
	{
		isFallStart = true;
	}
	else
	{
		isFallStart = false;
	}

	// �X�e�[�g�O������X�e�[�g�ύX�����������H
	if (nowState != nextState)
	{
		//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// �X�e�[�g���s
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		nextState = statePoolMap[nowState]->Update(this, _deltaTime);
	}

	// �X�e�[�g��������X�e�[�g�ύX���������H
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

void FallExplosionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
		_physicsTag == PhysicsTag::BREAK_GROUND_TAG || _physicsTag == PhysicsTag::ENEMY_TAG)
	{
		isHitExplosionObject = true;
	}
}
