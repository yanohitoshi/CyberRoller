#include "TrackingEnemyAttackArea.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectBase.h"
#include "SphereCollider.h"

TrackingEnemyAttackArea::TrackingEnemyAttackArea(const Tag& _objectTag, EnemyObjectBase* _ownerEnemy)
	:GameObject(false, _objectTag)
	, ownerEnemy(_ownerEnemy)
	, AttackArea(50.0f)
	, EnableTime(120)
{
	SetPosition(ownerEnemy->GetPosition());
	isEnable = true;
	disableCount = 0;

	//�W�����v�U������p��sphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::ENEMY_ATTACK_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),AttackArea };
	sphereCollider->SetObjectSphere(sphere);
}

TrackingEnemyAttackArea::~TrackingEnemyAttackArea()
{
}

void TrackingEnemyAttackArea::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�������X�V
	SetPosition(ownerEnemy->GetPosition());

	// ������ԂɂȂ��Ă�����
	if (!isEnable)
	{
		// �������Ԃ𐔂���
		++disableCount;
		// �L�����Ԃɓ��B������
		if (disableCount > EnableTime)
		{
			// �L����Ԃɂ���
			isEnable = true;
		}
	}
}

void TrackingEnemyAttackArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ���X�|�[����Ԃ�������Ԃ�
	if (ownerEnemy->GetNowState() == EnemyState::ENEMY_STATE_RESPAWN)
	{
		return;
	}

	// �v���C���[����������
	if (_hitObject.GetTag() == Tag::PLAYER &&_physicsTag == PhysicsTag::PLAYER_TAG && isEnable)
	{
		// �e�N���X���U����ԂɃZ�b�g
		ownerEnemy->SetIsAttack(true);
		isEnable = false;
		disableCount = 0;
	}
}
