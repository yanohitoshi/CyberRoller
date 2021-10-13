//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MoveBlockObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param  �������ɕK�v�ȃf�[�^�\����
*/
MoveBlockObject::MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, MoveBlockData _data)
	:GameObject(false, _objectTag)
	, CorrectionAabbValue(0.1f)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _data.distance;
	direction = _data.direction;
	moveSpeed = _data.speed;
	moveTag = _data.tag;
	inversionFlag = false;
	isPushBackToPlayer = true;
	isSendVelocityToPlayer = true;
	isChackGroundToPlayer = true;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/lightGround.gpmesh"));

	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::MOVE_GROUND_TAG, GetOnCollisionFunc());
	aabb = mesh->GetBox();
	//�v���C���[�����蔲���Ȃ��悤��AABB�̃T�C�Y��␳
	aabb.max.y += CorrectionAabbValue;
	aabb.min.y -= CorrectionAabbValue;
	boxCollider->SetObjectBox(aabb);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
MoveBlockObject::~MoveBlockObject()
{
	//geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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

/*
@fn �������֐�
*/
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

/*
@fn ���]�`�F�b�N�����֐�
*/
void MoveBlockObject::ChackInversionProcess()
{
	// ���������̃^�O�����ď�����ς���
	switch (moveTag)
	{
	case MOVE_X:
		// X���̏���
		ChackAxisX();
		break;
	case MOVE_Y:
		// Y���̏���
		ChackAxisY();
		break;
	case MOVE_Z:
		// Z���̏���
		ChackAxisZ();
		break;
	}
}

/*
@fn X�����]�`�F�b�N�����֐�
*/
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

/*
@fn Y�����]�`�F�b�N�����֐�
*/
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

/*
@fn Z�����]�`�F�b�N�����֐�
*/
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