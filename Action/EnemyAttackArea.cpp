//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"
#include "EnemyAttackArea.h"
#include "EnemyObjectBase.h"
#include "SphereCollider.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�e�N���X�̃|�C���^
*/
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

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
EnemyAttackArea::~EnemyAttackArea()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void EnemyAttackArea::UpdateGameObject(float _deltaTime)
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

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	�����蔻��^�O
*/
void EnemyAttackArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ���X�|�[����Ԃ�������Ԃ�
	if (ownerEnemy->GetNowState() == EnemyState::ENEMY_STATE_RESPAWN)
	{
		return;
	}

	// �v���C���[����������
	if (_hitObject.GetTag() == Tag::PLAYER && _physicsTag == PhysicsTag::PLAYER_TAG && isEnable)
	{
		// �e�N���X���U����ԂɃZ�b�g
		ownerEnemy->SetIsAttack(true);
		isEnable = false;
		disableCount = 0;
	}
}
