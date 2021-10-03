#include "TrackingEnemyObject.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectStateRespawn.h"
#include "EnemyObjectStateDead.h"
#include "TrackingEnemyStateIdle.h"
#include "TrackingEnemyStateTracking.h"
#include "TrackingEnemyStateMoving.h"
#include "TrackingEnemyStateTurn.h"
#include "TrackingEnemyStateReposition.h"
#include "TrackingEnemyStateAttack.h"
#include "BoxCollider.h"
#include "PlayerTrackingArea.h"
#include "EnemyAttackArea.h"

TrackingEnemyObject::TrackingEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject, float _areaValue)
	: EnemyObjectBase(_pos, false, _objectTag, _moveSpeed, _trackingObject)
	, Angle(180.0f)
{
	//GameObject�����o�ϐ��̏�����
	state = Active;
	scale = Vector3(2.0f, 2.0f, 2.0f);
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	forwardVec = Vector3::NegUnitX;
	charaForwardVec = Vector3::NegUnitX;
	SetScale(scale);

	isTracking = false;
	isDeadFlag = false;
	isAttack = false;
	isPushBackToPlayer = true;
	isOtherEnemyHit = false;

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
	statePools.push_back(new TrackingEnemyStateIdle);
	statePools.push_back(new EnemyObjectStateDead);
	statePools.push_back(new EnemyObjectStateRespawn);
	statePools.push_back(new TrackingEnemyStateMoving);
	statePools.push_back(new TrackingEnemyStateTurn);
	statePools.push_back(new TrackingEnemyStateTracking);
	statePools.push_back(new TrackingEnemyStateReposition);
	statePools.push_back(new TrackingEnemyStateAttack);

	//anim�ϐ��𑬓x1.0f�ōĐ�
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);
	// state�̏�����
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;

	new PlayerTrackingArea(Tag::PLAYER_TRACKING_AREA, this, _areaValue);
	new EnemyAttackArea(Tag::PLAYER_TRACKING_AREA, this);

	//Z����180�x��]������
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

TrackingEnemyObject::~TrackingEnemyObject()
{
}

void TrackingEnemyObject::UpdateGameObject(float _deltaTime)
{
	// AABB���X�V
	aabb = boxCollider->GetWorldBox();

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

	isTracking = false;
	isOtherEnemyHit = false;
	forwardVec = charaForwardVec;
}

void TrackingEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
	// �����x�ϐ�
	Vector3 ment = Vector3::Zero;

	CalcCollisionFixVec(myAABB, pairAABB, ment);

	// �����߂��v�Z���l�����|�W�V�������X�V
	SetPosition(position + ment);
}

void TrackingEnemyObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �W�����v�A�^�b�N�v���C���[��������
	if (_hitObject.GetTag() == Tag::JUMP_ATTACK_PLAYER)
	{
		// ���S�t���O��true��
		isDeadFlag = true;
	}

	// ���̓G�܂��̓O���E���h�Ɠ���������
	if (_hitObject.GetTag() == Tag::ENEMY || _hitObject.GetTag() == Tag::GROUND)
	{
		// �����߂�
		FixCollision(aabb, _hitObject.aabb);
	}
}
