//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MoveBlockObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

MoveBlockObject::MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,const Vector3& _distance, const Vector3& _direction, const float& _speed, MoveDirectionTag _moveTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _distance;
	direction = _direction;
	moveSpeed = _speed;
	moveTag = _moveTag;
	inversionFlag = false;
	isPushBackToPlayer = true;
	isSendVelocityToPlayer = true;
	isChackGroundToPlayer = true;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/groundModel/box.gpmesh"));
	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::MOVE_GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

}

MoveBlockObject::~MoveBlockObject()
{
}

void MoveBlockObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();

	// ������
	MovableProcess();

	// �ړ���Ԋm�F
	ChackInversionProcess();

	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;

	// �|�W�V�������X�V
	SetPosition(position);

}

void MoveBlockObject::MovableProcess()
{
	// ���]���邩�ǂ����t���O�𔻒肵����ɉ����đ��x��t�^
	if (inversionFlag == false)
	{
		// �ʏ�̑��x����
		velocity = direction * moveSpeed;
	}
	else if (inversionFlag == true)
	{
		// ���]�������x����
		velocity = direction * moveSpeed * -1.0f;
	}
}

void MoveBlockObject::ChackInversionProcess()
{
	// ����������Tag���Ƃɔ��]������������Ĕ��]����
	if (moveTag == MoveDirectionTag::MOVE_X)
	{
		// X���̏���
		ChackAxisX();
		// ���݂̎d�l��1�̎��ړ������s��Ȃ����ߕԂ�
		return;
	}

	if (moveTag == MoveDirectionTag::MOVE_Y)
	{
		// Y���̏���
		ChackAxisY();
		// ���݂̎d�l��1�̎��ړ������s��Ȃ����ߕԂ�
		return;
	}

	if (moveTag == MoveDirectionTag::MOVE_Z)
	{
		// Z���̏���
		ChackAxisZ();
		// ���݂̎d�l��1�̎��ړ������s��Ȃ����ߕԂ�
		return;
	}
}

void MoveBlockObject::ChackAxisX()
{
	// ���B�_�ɒB���Ă����甽�]
	if (position.x >= goalPos.x && direction.x == 1.0f || position.x <= goalPos.x && direction.x == -1.0f)
	{
		inversionFlag = true;
	}

	// ���̈ʒu�ɒB���Ă����甽�]
	if (position.x <= initPos.x && direction.x == 1.0f || position.x >= initPos.x && direction.x == -1.0f)
	{
		inversionFlag = false;
	}
}

void MoveBlockObject::ChackAxisY()
{
	// ���B�_�ɒB���Ă����甽�]
	if (position.y >= goalPos.y && direction.y == 1.0f || position.y <= goalPos.y && direction.y == -1.0f)
	{
		inversionFlag = true;
	}

	// ���̈ʒu�ɒB���Ă����甽�]
	if (position.y <= initPos.y && direction.y == 1.0f || position.y >= initPos.y && direction.y == -1.0f)
	{
		inversionFlag = false;
	}
}

void MoveBlockObject::ChackAxisZ()
{
	// ���B�_�ɒB���Ă����甽�]
	if (position.z >= goalPos.z && direction.z == 1.0f || position.z <= goalPos.z && direction.z == -1.0f)
	{
		inversionFlag = true;
	}

	// ���̈ʒu�ɒB���Ă����甽�]
	if (position.z <= initPos.z && direction.z == 1.0f || position.z >= initPos.z && direction.z == -1.0f)
	{
		inversionFlag = false;
	}
}
