#include "TrackingEnemyObject.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "TrackingEnemyStateDead.h"
#include "TrackingEnemyStateIdle.h"
#include "TrackingEnemyStateTracking.h"
#include "TrackingEnemyStateMoving.h"
#include "TrackingEnemyStateTurn.h"
#include "TrackingEnemyStateReposition.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

TrackingEnemyObject::TrackingEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject)
	: EnemyObjectBase(_pos, false, _objectTag, _moveSpeed, _trackingObject)
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

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = skeltalMeshComponent->GetMesh();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::NORMAL_ENEMY_TAG, GetOnCollisionFunc());
	//enemyBox = mesh->GetBox();
	enemyBox = { Vector3(-10.0f,-10.0f,-50.0f),Vector3(10.0f,10.0f,10.0f) };
	boxCollider->SetObjectBox(enemyBox);

	//�W�����v�U������p��sphereCollider
	trackingSphereCol = new SphereCollider(this, ColliderComponent::ENEMY_TRACKING_TAG, std::bind(&TrackingEnemyObject::OnCollisionTracking, this, std::placeholders::_1));
	Sphere jumpAttackSphere = { Vector3(0.0f,0.0f,0.0f),800.0f };
	trackingSphereCol->SetObjectSphere(jumpAttackSphere);

	// state�v�[���̏�����
	// �����Ԃɔz��ɒǉ����Ă����̂ŃX�e�[�^�X�̗񋓂ƍ������Ԃɒǉ�
	statePools.push_back(new TrackingEnemyStateIdle);
	statePools.push_back(new TrackingEnemyStateDead);
	statePools.push_back(new TrackingEnemyStateMoving);
	statePools.push_back(new TrackingEnemyStateTurn);
	statePools.push_back(new TrackingEnemyStateTracking);
	statePools.push_back(new TrackingEnemyStateReposition);

	//anim�ϐ��𑬓x1.0f�ōĐ�
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)], 1.0f);
	// state�̏�����
	nowState = EnemyState::ENEMY_STATE_IDLE;
	nextState = EnemyState::ENEMY_STATE_IDLE;
}

TrackingEnemyObject::~TrackingEnemyObject()
{
}

void TrackingEnemyObject::UpdateGameObject(float _deltaTime)
{
	if (isTracking)
	{
		nextState = EnemyState::ENEMY_STATE_TRACKING;
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
}

void TrackingEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
}

void TrackingEnemyObject::OnCollision(const GameObject& _hitObject)
{
}

void TrackingEnemyObject::OnCollisionTracking(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		isTracking = true;
	}
}
