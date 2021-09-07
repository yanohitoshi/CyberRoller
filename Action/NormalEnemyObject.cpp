#include "NormalEnemyObject.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "EnemyObjectStateBase.h"
#include "BoxCollider.h"

NormalEnemyObject::NormalEnemyObject(const Vector3& _pos, const Tag _objectTag)
	: EnemyObjectBase(_pos, false , _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	state = Active;
	scale = Vector3(1.0f, 1.0f, 1.0f);
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	SetScale(scale);

	//���f���`��p�̃R���|�[�l���g
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mes h���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/enemy_robo_model/SK_Dron_01.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/enemy_robo_model/SK_Dron_01.gpskel"));

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	//�A�j���\�V�����p�̉ϒ��z������T�C�Y
	animTypes.resize(static_cast<unsigned int>(EnemyState::ENEMY_STATE_NUM));

	//-----------�A�j���[�V������ǂݍ���-----------------//
	// �A�C�h�����O�A�j���[�V����
	animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/enemy_robo_model/Dron_01_Idle.gpanim", true);
	//// ���ȏ���͂��Ȃ������ۂ̃A�C�h�����O�A�j���[�V�����i�_���X�j
	//animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_RUN)] = RENDERER->GetAnimation("Assets/Model/robo_model/Tut_Hip_Hop_Dance.gpanim", true);
	//// ����A�j���[�V����
	//animTypes[static_cast<unsigned int>(EnemyState::ENEMY_STATE_RUN_TURN)] = RENDERER->GetAnimation("Assets/Model/robo_model/Running.gpanim", true);
	//// ���肾���A�j���[�V����
	//animTypes[static_cast<unsigned int>(EnemyState::PLAYER_STATE_RUN_START)] = RENDERER->GetAnimation("Assets/Model/robo_model/Idle_To_Sprint_2.gpanim", false);

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = skeltalMeshComponent->GetMesh();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::NORMAL_ENEMY_TAG, GetOnCollisionFunc());
	enemyBox = mesh->GetBox();
	boxCollider->SetObjectBox(enemyBox);

	//// state�v�[���̏�����
	//// �����Ԃɔz��ɒǉ����Ă����̂ŃX�e�[�^�X�̗񋓂ƍ������Ԃɒǉ�
	//statePools.push_back(new PlayerObjectStateIdle);
	//statePools.push_back(new PlayerObjectStateIdlingDance);
	//statePools.push_back(new PlayerObjectStateRun);

}

NormalEnemyObject::~NormalEnemyObject()
{
}

void NormalEnemyObject::UpdateGameObject(float _deltaTime)
{
}

void NormalEnemyObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
}

void NormalEnemyObject::OnCollision(const GameObject& _hitObject)
{
}
