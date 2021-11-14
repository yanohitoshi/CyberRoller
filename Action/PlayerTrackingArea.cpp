//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerTrackingArea.h"
#include "EnemyObjectStateBase.h"
#include "TrackingEnemyObject.h"
#include "SphereCollider.h"

/*
@fn �R���X�g���N�^
@param	�I�u�W�F�N�g���ʗptag
@param	�e�ƂȂ�G�N���X�̃|�C���^
@param	�G���A�̑傫���ƂȂ�l
*/
PlayerTrackingArea::PlayerTrackingArea(const Tag& _objectTag, EnemyObjectBase* _ownerEnemy, float _areaValue)
	:GameObject(false, _objectTag)
	, owner(_ownerEnemy)
{
	SetPosition(owner->GetPosition());

	//�W�����v�U������p��sphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::PLAYER_TRACKING_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),_areaValue };
	sphereCollider->SetObjectSphere(sphere);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PlayerTrackingArea::~PlayerTrackingArea()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void PlayerTrackingArea::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�������Œ�
	SetPosition(position);
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	�����蔻��^�O
*/
void PlayerTrackingArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ���X�|�[����Ԃ�������Ԃ�
	if (owner->GetNowState() == EnemyState::ENEMY_STATE_RESPAWN)
	{
		return;
	}

	// �v���C���[����������
	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		// �e�N���X��ǐՏ�ԂɃZ�b�g
		owner->SetIsTracking(true);
		// �ǐՂ���Ώۂ̃|�W�V�������Z�b�g
		owner->SetAttackObjectPosition(_hitObject.GetPosition());
	}
}
