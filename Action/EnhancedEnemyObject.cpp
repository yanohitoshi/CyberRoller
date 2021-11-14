#include "EnhancedEnemyObject.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectStateRespawn.h"
#include "EnemyObjectStateDead.h"
#include "EnhancedEnemyStateIdle.h"
#include "EnhancedEnemyStateFlinch.h"
#include "EnemyObjectStateTracking.h"
#include "EnemyObjectStateTurn.h"
#include "EnemyObjectStateReposition.h"
#include "EnemyObjectStateAttack.h"
#include "BoxCollider.h"
#include "PlayerTrackingArea.h"
#include "EnemyFlinchEffectManager.h"
#include "EnemyAttackArea.h"

EnhancedEnemyObject::EnhancedEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed, float _areaValue)
	: EnemyObjectBase(_pos, false, _objectTag, _moveSpeed)
	, Angle(180.0f)
{
	//GameObject�����o�ϐ��̏�����
	state = Active;
	scale = Vector3(3.0f, 3.0f, 3.0f);
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	forwardVec = Vector3::NegUnitX;
	charaForwardVec = Vector3::NegUnitX;
	SetScale(scale);

	isTracking = false;
	isDead = false;
	isAttack = false;
	isFlinch = false;
	isPushBackToPlayer = true;

	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mes h���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Enemy/EnemyModel/SK_Dron_01_Tracking.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Enemy/EnemyModel/SK_Dron_01.gpskel"));
	// mesh�����擾
	mesh = skeltalMeshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	//�A�j���\�V�����p�̉ϒ��z������T�C�Y
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------�A�j���[�V������ǂݍ���-----------------//
	// �A�C�h�����O�A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Idle.gpanim", true);
	// ���S���̃A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_DEAD)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Dead.gpanim", false);
	// ���ݎ��̃A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_FLINCH)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Get_Hit.gpanim", false);
	// �^�[���A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_TURN)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_rotatation_180_L.gpanim", false);
	// �U���A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_ATTACK)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Attack.gpanim", false);

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::ENEMY_TAG, GetOnCollisionFunc());
	enemyBox = { BoxMin,BoxMax };
	boxCollider->SetObjectBox(enemyBox);

	// state��statePool�p�}�b�v�ɒǉ�
	AddStatePoolMap(new EnhancedEnemyStateIdle, EnemyState::ENEMY_STATE_IDLE);
	AddStatePoolMap(new EnemyObjectStateDead, EnemyState::ENEMY_STATE_DEAD);
	AddStatePoolMap(new EnemyObjectStateRespawn, EnemyState::ENEMY_STATE_RESPAWN);
	AddStatePoolMap(new EnhancedEnemyStateFlinch, EnemyState::ENEMY_STATE_FLINCH);
	AddStatePoolMap(new EnemyObjectStateAttack, EnemyState::ENEMY_STATE_ATTACK);
	AddStatePoolMap(new EnemyObjectStateTurn, EnemyState::ENEMY_STATE_TURN);
	AddStatePoolMap(new EnemyObjectStateTracking, EnemyState::ENEMY_STATE_TRACKING);
	AddStatePoolMap(new EnemyObjectStateReposition, EnemyState::ENEMY_STATE_REPOSITION);

	//anim�ϐ��𑬓x1.0f�ōĐ�
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);
	// state�̏�����
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;

	new PlayerTrackingArea(Tag::PLAYER_TRACKING_AREA, this, _areaValue);
	new EnemyAttackArea(Tag::PLAYER_TRACKING_AREA, this);
	new EnemyFlinchEffectManager(this);

	//Z����180�x��]������
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

EnhancedEnemyObject::~EnhancedEnemyObject()
{
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_IDLE);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_DEAD);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_RESPAWN);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_FLINCH);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_ATTACK);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_TURN);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_TRACKING);
	RemoveStatePoolMap(EnemyState::ENEMY_STATE_REPOSITION);
	ClearStatePoolMap();
}

void EnhancedEnemyObject::UpdateGameObject(float _deltaTime)
{
	// AABB���X�V
	aabb = boxCollider->GetWorldBox();

	if (isAttack && !isDead)
	{
		nextState = EnemyState::ENEMY_STATE_ATTACK;
	}

	if (isFlinch && !isDead)
	{
		nextState = EnemyState::ENEMY_STATE_FLINCH;
	}

	if (isDead)
	{
		nextState = EnemyState::ENEMY_STATE_DEAD;
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

	isTracking = false;
	forwardVec = charaForwardVec;
}

void EnhancedEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
	// �����x�ϐ�
	Vector3 ment = Vector3::Zero;

	CalcCollisionFixVec(myAABB, pairAABB, ment);

	// �����߂��v�Z���l�����|�W�V�������X�V
	SetPosition(position + ment);
}

void EnhancedEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �W�����v�A�^�b�N�v���C���[��������
	if (_physicsTag == PhysicsTag::EXPLOSION_AREA_TAG)
	{
		// ���S�t���O��true��
		isDead = true;
		defeatedObjectPosition = _hitObject.GetPosition();
	}

	// �W�����v�A�^�b�N�v���C���[��������
	if (_physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		// ���S�t���O��true��
		isFlinch = true;
		defeatedObjectPosition = _hitObject.GetPosition();
	}

	// ���̓G�܂��̓O���E���h�Ɠ���������
	if (_hitObject.GetTag() == Tag::ENEMY)
	{
		aabb = boxCollider->GetWorldBox();
		// �����߂�
		FixCollision(aabb, _hitObject.GetAabb());
	}

	bool isPushBack = _physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
		_physicsTag == PhysicsTag::WALL_TAG || _physicsTag == PhysicsTag::SWITCH_BASE_TAG ||
		_physicsTag == PhysicsTag::SWITCH_TAG;

	if (isPushBack)
	{
		FixCollision(aabb, _hitObject.GetAabb());
	}
}
