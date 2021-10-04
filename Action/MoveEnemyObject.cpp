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

MoveEnemyObject::MoveEnemyObject(const Vector3& _pos, const Tag _objectTag,GameObject* _trackingObject , float _moveSpeed,const Vector3& _moveDir, float _moveDistance, MoveEnemyTag _moveEnemyTag)
	: EnemyObjectBase(_pos, false, _objectTag, _trackingObject, _moveSpeed, _moveDir, _moveDistance, _moveEnemyTag)
{
	//GameObject�����o�ϐ��̏�����
	state = Active;
	scale = Size;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	forwardVec = Vector3::NegUnitX;
	charaForwardVec = Vector3::NegUnitX;
	SetScale(scale);

	isAttack = false;
	isDeadFlag = false;

	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mes h���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Enemy/EnemyModel/SK_Dron_01.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Enemy/EnemyModel/SK_Dron_01.gpskel"));

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	//�A�j���\�V�����p�̉ϒ��z������T�C�Y
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------�A�j���[�V������ǂݍ���-----------------//
	// �A�C�h�����O�A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Idle.gpanim", true);
	// ���S���̃A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_DEAD)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Dead.gpanim", false);
	// �^�[���A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_TURN)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_rotatation_180_L.gpanim", false);
	// �U���A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_ATTACK)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAnimation/Dron_01_Attack.gpanim", false);
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::ENEMY_TAG, GetOnCollisionFunc());
	enemyBox = { BoxMin,BoxMax };
	boxCollider->SetObjectBox(enemyBox);

	// state�v�[���̏�����
	// �����Ԃɔz��ɒǉ����Ă����̂ŃX�e�[�^�X�̗񋓂ƍ������Ԃɒǉ�
	statePools.push_back(new MoveEnemyObjectStateIdle);
	statePools.push_back(new EnemyObjectStateDead);
	statePools.push_back(new EnemyObjectStateRespawn);
	statePools.push_back(new EnemyObjectStateAttack);
	statePools.push_back(new MoveEnemyObjectStateMoving);
	statePools.push_back(new MoveEnemyObjectStateTurn);

	//anim�ϐ��𑬓x1.0f�ōĐ�
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);
	// state�̏�����
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;

	new EnemyAttackArea(Tag::PLAYER_TRACKING_AREA, this);
}

MoveEnemyObject::~MoveEnemyObject()
{
}

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

	// �X�e�[�g�O������X�e�[�g�ύX�����������H
	if (nowState != nextState)
	{
		statePools[static_cast<unsigned int>(nextState)]->Enter(this, _deltaTime);
		nowState = nextState;
		return;
	}

	// �X�e�[�g���s
	nextState = statePools[static_cast<unsigned int>(nowState)]->Update(this, _deltaTime);

	// �X�e�[�g��������X�e�[�g�ύX���������H
	if (nowState != nextState)
	{
		statePools[static_cast<unsigned int>(nextState)]->Enter(this, _deltaTime);
		nowState = nextState;
	}

	isAttack = false;
}

void MoveEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
}

void MoveEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER)
	{
		isDeadFlag = true;
	}
}