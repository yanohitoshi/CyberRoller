//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
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
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�I�u�W�F�N�g���ʗptag
*/
ExplosionObject::ExplosionObject(const Vector3& _pos, const Tag _objectTag)
	: ExplosionObjectBase(_objectTag)
	, ShiftPositionZ(100.0f)
{
	//GameObject�����o�ϐ��̏�����
	velocity.Zero;

	position = _pos;
	position.z += ShiftPositionZ;
	SetPosition(position);
	// �����|�W�V������ۑ�
	firstPosition = position;

	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isStartExplosion = false;
	isHitJumpAttackPlayer = false;
	isHitExplosionObject = false;
	hitPosition = Vector3(0.0f,0.0f,0.0f);

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Bomb/model/bomb.gpmesh"));
	meshComponent->SetEmissiveColor(Color::LightBlue);

	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::BOMB_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-100.0f,-100.0f,-100.0f),Vector3(100.0f,100.0f,100.0f) };
	boxCollider->SetObjectBox(aabb);

	// �X�e�[�g�}�b�v��state�N���X��ǉ�
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
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ExplosionObject::~ExplosionObject()
{
	// Map�̌�Еt��
	RemoveStatePoolMap(ExplosionObjectState::IDLE);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION_START);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION);
	RemoveStatePoolMap(ExplosionObjectState::RESPAWN);
	ClearStatePoolMap();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ExplosionObject::UpdateGameObject(float _deltaTime)
{
	if (isStartExplosion && !isExplode && nowState != ExplosionObjectState::EXPLOSION_START)
	{
		nextState = ExplosionObjectState::EXPLOSION_START;
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

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	�����蔻��^�O
*/
void ExplosionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �A�C�h�����O��Ԓ��ɃW�����v�A�^�b�N�v���C���[�Ɠ���������
	if (_physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG && nowState == ExplosionObjectState::IDLE)
	{
		isStartExplosion = true;
		isHitJumpAttackPlayer = true;
		hitPosition = _hitObject.GetPosition();
	}

	// �A�C�h�����O��Ԓ��ɃW�����v�A�^�b�N�v���C���[�Ɠ���������
	bool isHitUnMoveExplosionObject = _physicsTag == PhysicsTag::PLAYER_TAG && nowState == ExplosionObjectState::IDLE ||
		_physicsTag == PhysicsTag::ENEMY_TAG && nowState == ExplosionObjectState::IDLE;
	if(isHitUnMoveExplosionObject)
	{
		isStartExplosion = true;
		isHitJumpAttackPlayer = false;
		hitPosition = Vector3::Zero;
	}

	// �����J�n���̎�
	if (nowState == ExplosionObjectState::EXPLOSION_START)
	{
		// ����������I�u�W�F�N�g�ɓ���������
		bool isImmediateExplosionObject = _physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
			_physicsTag == PhysicsTag::BREAK_GROUND_TAG || _physicsTag == PhysicsTag::ENEMY_TAG;

		if (isImmediateExplosionObject)
		{
			isHitExplosionObject = true;
		}
	}
}