//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PushBoardObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "PushBoxObject.h"

PushBoardObject::PushBoardObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, PushBoxData _pushBoxData)
	:GameObject(false, _objectTag)
	, MoveSpeed(_pushBoxData.speed)
	, CutBackSpeed(_pushBoxData.cutBackSpeed)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _pushBoxData.distance;
	direction = _pushBoxData.direction;
	moveTag = _pushBoxData.tag;
	inversionFlag = false;
	isSendVelocityToPlayer = true;
	isPushBackToPlayer = true;
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/box.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::MOVE_GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
}

PushBoardObject::~PushBoardObject()
{
}

void PushBoardObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();

	// ������
	MovableProcess();

	// ���]���邩�`�F�b�N
	ChackInversionProcess();

	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;

	// �|�W�V�������X�V
	SetPosition(position);
}

void PushBoardObject::ChackInversionProcess()
{
	// @fix

	//�O��ړ��p����
	if (moveTag == MoveDirectionTag::MOVE_X)
	{
		// X���̏���
		ChackAxisX();
		// ���݂̎d�l��1�̎��ړ������s��Ȃ����ߕԂ�
		return;
	}

	//���E�ړ��p����
	if (moveTag == MoveDirectionTag::MOVE_Y)
	{
		// Y���̏���
		ChackAxisY();
		// ���݂̎d�l��1�̎��ړ������s��Ȃ����ߕԂ�
		return;
	}

	//�㉺�ړ��p����
	if (moveTag == MoveDirectionTag::MOVE_Z)
	{
		// Z���̏���
		ChackAxisZ();
		// ���݂̎d�l��1�̎��ړ������s��Ȃ����ߕԂ�
		return;
	}



}

void PushBoardObject::MovableProcess()
{
	// ���x�𔽓]���邩�ǂ����𔻒�
	if (inversionFlag == false)
	{
		// �����ɑ��x���|����
		velocity = direction * MoveSpeed;
	}
	else if (inversionFlag == true)
	{
		// �߂�ۂ͌������|����
		velocity = direction * (MoveSpeed * CutBackSpeed) * -1.0f;
	}
}

void PushBoardObject::ChackAxisX()
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

void PushBoardObject::ChackAxisY()
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

void PushBoardObject::ChackAxisZ()
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
