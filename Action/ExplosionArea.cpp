//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionArea.h"
#include "ExplosionObjectBase.h"
#include "SphereCollider.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�e�N���X�̃|�C���^
*/
ExplosionArea::ExplosionArea(const Tag& _objectTag, ExplosionObjectBase* _owner)
	:GameObject(false, _objectTag)
	, owner(_owner)
	, ExplosionAreaSize(300.0f)
{
	// ������
	SetState(State::Active);
	SetPosition(owner->GetPosition());

	//�W�����v�U������p��sphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::EXPLOSION_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),ExplosionAreaSize };
	sphereCollider->SetObjectSphere(sphere);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ExplosionArea::~ExplosionArea()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ExplosionArea::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�����X�V
	SetPosition(owner->GetPosition());

	// �e��������Ԃ�����
	isActive = owner->GetIsExplode();
	if (isActive)
	{
		SetState(State::Active);
	}
	else
	{
		SetState(State::Disabling);
	}
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	�����蔻��^�O
*/
void ExplosionArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}