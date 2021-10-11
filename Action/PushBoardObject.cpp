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
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param  �v�b�V���{�[�h���X�V����̂Ɏg�p����f�[�^�\����
*/
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

	////���f���`��p�̃R���|�[�l���g
	//meshComponent = new MeshComponent(this, false, false);
	////Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	//meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/box.gpmesh"));
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/groundModel/lightGround.gpmesh"), GeometryInstanceType::G_PUDH_BOARD, 500);
	geometryInstanceComponent->AddGeometryInstanceManager();
	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = geometryInstanceComponent->GetMesh();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::MOVE_GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PushBoardObject::~PushBoardObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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

/*
@fn ���]�`�F�b�N�����֐�
*/
void PushBoardObject::ChackInversionProcess()
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
@fn �������֐�
*/
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

/*
@fn X�����]�`�F�b�N�����֐�
*/
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

/*
@fn Y�����]�`�F�b�N�����֐�
*/
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

/*
@fn Z�����]�`�F�b�N�����֐�
*/
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