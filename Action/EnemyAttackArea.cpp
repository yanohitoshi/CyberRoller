#include "EnemyAttackArea.h"
#include "EnemyObjectBase.h"
#include "SphereCollider.h"

EnemyAttackArea::EnemyAttackArea(const Tag& _objectTag, EnemyObjectBase* _ownerEnemy)
	:GameObject(false, _objectTag)
	, ownerEnemy(_ownerEnemy)
	, AttackArea(50.0f)
	, EnableTime(60)
{
	SetPosition(ownerEnemy->GetPosition());
	isEnable = true;
	disableCount = 0;

	//�W�����v�U������p��sphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::ENEMY_ATTACK_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),AttackArea };
	sphereCollider->SetObjectSphere(sphere);
}

EnemyAttackArea::~EnemyAttackArea()
{
}

void EnemyAttackArea::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�������X�V
	SetPosition(ownerEnemy->GetPosition());

	if (!isEnable)
	{
		++disableCount;
		if (disableCount > EnableTime)
		{
			isEnable = true;
		}
	}
}

void EnemyAttackArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �v���C���[����������
	if (_hitObject.GetTag() == Tag::PLAYER &&_physicsTag == PhysicsTag::PLAYER_TAG && isEnable)
	{
		// �e�N���X���U����ԂɃZ�b�g
		ownerEnemy->SetIsAttack(true);
		isEnable = false;
		disableCount = 0;
	}
}
