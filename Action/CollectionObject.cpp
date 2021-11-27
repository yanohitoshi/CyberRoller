//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CollectionObject.h"
#include "MeshComponent.h"
#include "RenderingObjectManager.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "CollectionEffectManager.h"
#include "CrystalEffectManager.h"
#include "CollectionUI.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�I�u�W�F�N�g���ʗptag
@param	���Ԗڂ̎��W�����𔻒肷��^�O
*/
CollectionObject::CollectionObject(const Vector3& _pos, const Tag& _objectTag, CollectionTag _collectionTag)
	: GameObject(false, _objectTag)
	, ShiftPositionZ(100.0f)
	, CollectedSpeed(1200.0f)
	, VerticalMoveSpeed(50.0f)
	, ChangeRateTime(30)
	, CollectedMoveTime(15)
	, CollectedVisibleTime(60)
{
	//GameObject�����o�ϐ��̏�����
	velocity.Zero;
	position = _pos;
	position.z += ShiftPositionZ;
	SetPosition(position);
	SetScale(Vector3(25.0f, 25.0f, 25.0f));
	collectionTag = _collectionTag;
	value = 0.0f;
	rate = 0.0f;
	frameCount = 0;
	collectedRotationAngle = 0.0f;
	collectedCount = 0;
	isCollected = false;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Collection/model/SM_Small_Gems.gpmesh"));
	
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::COLLECTION_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-5.0f,-5.0f,-5.0f),Vector3(5.0f,5.0f,15.0f) };
	boxCollider->SetObjectBox(aabb);

	new CollectionEffectManager(this);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CollectionObject::~CollectionObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionObject::UpdateGameObject(float _deltaTime)
{
	// �`�悳��ĂȂ�������return
	if (!meshComponent->GetVisible())
	{
		return;
	}

	// AABB���X�V
	aabb = boxCollider->GetWorldBox();

	// ���W����Ă�����
	if (isCollected)
	{
		// ���W����Ă��鎞�̊֐����Ăяo��
		Collected(_deltaTime);
	}
	else
	{
		// ����ȊO�̎��̈ړ�����
		Movable(_deltaTime);
	}
}

/*
@fn ��]�����֐�
@param ��]����p�x
@param ��]���鎲
*/
void CollectionObject::RotationProcess(float _angle, Vector3 _axis)
{
	//_axis����_angle�x��]������
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
@fn �������֐�
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionObject::Movable(float _deltaTime)
{
	// �t���[���J�E���g�𐔂���
	++frameCount;

	// ���[�g��ύX���鎞�Ԃ�������v�Z���Ȃ���
	if (frameCount % ChangeRateTime == 0)
	{
		++value;
		rate = Math::Cos(value);
	}

	// ���[�g�ɑ��x���|����
	velocity.z = rate * VerticalMoveSpeed;

	// �|�W�V�����X�V
	SetPosition(position + velocity * _deltaTime);
}

/*
@fn ���W���ꂽ���̏����֐�
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionObject::Collected(float _deltaTime)
{
	// ���W����Ă���̃J�E���g�𐔂���
	++collectedCount;
	// ��]�p��1����
	++collectedRotationAngle;
	// ��]����
	RotationProcess(collectedRotationAngle, Vector3::UnitZ);

	// ���W���ꂽ��ړ����鎞�Ԃ܂ňړ�����
	if (collectedCount <= CollectedMoveTime)
	{
		velocity.z = CollectedSpeed;
		SetPosition(position + velocity * _deltaTime);
	}

	// ���Ԃ�������`���؂�
	if (collectedCount >= CollectedVisibleTime)
	{
		meshComponent->SetVisible(false);
	}
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void CollectionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �v���C���[�������̓W�����v�A�^�b�N�v���C���[�ɓ���������
	if (_physicsTag == PhysicsTag::PLAYER_TAG || _physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		// ���W��Ԃɂ���
		isCollected = true;
	}
}