//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "JumpAttackPlayerObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "JumpAttackEffectManager.h"
#include "PlayerAttackHitEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�I�u�W�F�N�g�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
*/
JumpAttackPlayerObject::JumpAttackPlayerObject(PlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag)
	: GameObject(false, _objectTag)
	, Rotation(10.0f)
	, ShiftPositionZ(100.0f)
{
	ownerObject = _ownerObject;
	position = ownerObject->GetPosition();
	position.z += ShiftPositionZ;
	rotationAngle = 0.0f;
	isHIt = false;
	// �O���x�N�g��������
	forwardVec = ownerObject->GetForwardVec();

	SetPosition(position);
	SetScale(_size);
	SetState(State::Disabling);

	meshComponent = new MeshComponent(this, false, false);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/JumpAttackPlayerModel/JumpAttackPlayer.gpmesh"));
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�U������p��sphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::JUMP_ATTACK_PLAYER_TAG, GetOnCollisionFunc());
	Sphere jumpAttackSphere = { Vector3(0.0f,0.0f,0.0f),3.0f };
	sphereCollider->SetObjectSphere(jumpAttackSphere);

	// �W�����v�A�^�b�N���̃G�t�F�N�g���Ǘ�����N���X�𐶐�
	new JumpAttackEffectManager(this);
	// �q�b�g�G�t�F�N�g���Ǘ�����N���X�𐶐�
	new PlayerAttackHitEffectManager(ownerObject);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
JumpAttackPlayerObject::~JumpAttackPlayerObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void JumpAttackPlayerObject::UpdateGameObject(float _deltaTime)
{
	if (ownerObject->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
	{
		SetState(State::Active);
		meshComponent->SetVisible(true);
	}
	else
	{
		SetState(State::Disabling);
		meshComponent->SetVisible(false);
		isHIt = false;
	}

	if (state == State::Active && !isHIt)
	{
		rotationAngle += Rotation;
		//Z�����w��p�x��]������
		float radian = Math::ToRadians(rotationAngle);
		Quaternion rot = this->GetRotation();
		Quaternion inc(Vector3::UnitY, radian);
		Quaternion target = Quaternion::Concatenate(rot, inc);
		SetRotation(target);
	}

	position = ownerObject->GetPosition();
	position.z += 100.0f;
	SetPosition(position);
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void JumpAttackPlayerObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �G�Ɠ���������
	if (_hitObject.GetTag() == Tag::ENEMY || _physicsTag == PhysicsTag::SWITCH_TAG ||
		_physicsTag == PhysicsTag::BOMB_TAG)
	{
		// �q�b�g�t���O��true��
		isHIt = true;
		// �W�����v�A�^�b�N������Ԃɂ���
		ownerObject->SetIsJumpAttackSuccess(true);
	}
}