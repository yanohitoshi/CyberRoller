//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MoveWallBlock.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "RenderingObjectManager.h"
#include "Skeleton.h"
#include <string>
#include "BoxCollider.h"
#include "SandSmokeMakeManeger.h"
#include "MainCameraObject.h"
#include "FirstStageUI.h"
#include "PlayerObject.h"
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param	�������x
@param	�~�܂�ʒu
*/
MoveWallBlock::MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, float _speed, Vector3 _stopPos)
	: GameObject(false, _objectTag)
	, MoveSpeed(_speed)
	, stopPos(_stopPos)
	, ShiftPositionY(200.0f)
{
	//GameObject�����o�ϐ��̏�����
	position = Vector3(_p.x , _p.y - ShiftPositionY, _p.z);
	SetPosition(position);
	scale = _size;
	SetScale(scale);
	tag = _objectTag;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	openFlag = false;
	isPushBackToPlayer = true;
	isPushBackToCamera = true;
	SetCheckSwitchTag(tag);

	// �W�I���g���C���X�^���X�R���|�[�l���g�𐶐�
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/MoveWall/model/moveWallBox.gpmesh"), GeometryInstanceType::G_MOVE_WALL);
	// �W�I���g���C���X�^���X�}�l�[�W���[�N���X�ɒǉ�
	geometryInstanceComponent->AddGeometryInstanceManager();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::WALL_TAG, GetOnCollisionFunc());
	// �����蔻��̂�Y����傫���������̂Œ���
	AABB aabb = { Vector3(-1.0f,-2.0f,-1.0f),Vector3(1.0f,2.0f,1.0f) };
	boxCollider->SetObjectBox(aabb);

	// �y���G�t�F�N�g�̕t�^
	new SandSmokeMakeManeger(this);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
MoveWallBlock::~MoveWallBlock()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MoveWallBlock::UpdateGameObject(float _deltaTime)
{
	// ���[���h�{�b�N�X�̍X�V
	aabb = boxCollider->GetWorldBox();

	// �Ώۂ̃X�C�b�`�̏�Ԃ��`�F�b�N
	CheckSwitch(checkTag);

	// �I�[�v���t���O��true��������
	if (openFlag == true)
	{
		OpenWall(_deltaTime);
	}

	// �|�W�V�����̍X�V
	SetPosition(position);
}

/*
@fn �ǂ��J���֐�
@brief	�ǂ��J���������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MoveWallBlock::OpenWall(float _deltaTime)
{
	// �ړ����x��t�^
	velocity.z = MoveSpeed;
	// �|�W�V�����ύX
	position.z -= velocity.z * _deltaTime;

	// �~�܂�ׂ��ʒu�ɗ������~
	if (position.z <= stopPos.z)
	{
		// �I�[�v���t���O��false��
		openFlag = false;
		// ���x��0.0f��
		velocity.z = 0.0f;
	}
}

/*
@fn �X�C�b�`�̏�Ԃ��m�F����֐�
@param	�ǂ̎�ނ�object�����肷��p��Tag
@param	�t���[�����[�g�Œ�pdeltaTime
*/
void MoveWallBlock::CheckSwitch(Tag& _tag)
{
	// �`�F�b�N�p�ϒ��z��
	std::vector<GameObject*> switches;
	// �ΏۂƂȂ�X�C�b�`�̉ϒ��z���T��
	switches = GameObject::FindGameObject(_tag);
	// ���݂���X�C�b�`��ON�ɂȂ��Ă���X�C�b�`�𐔂��邽�߂̃J�E���g������
	int switchCount = 0;
	int flagCount = 0;

	// �ϒ��z����̃X�C�b�`���`�F�b�N
	for (auto itr : switches)
	{
		// ���ݐ��𐔂���
		++switchCount;
		// �X�C�b�`��ON�̏�Ԃ�������
		if (itr->GetSwitchFlag() == true)
		{
			// ON�̐��𐔂���
			++flagCount;
		}
	}

	// ���݂���X�C�b�`�̐���ON�ɂȂ��Ă���X�C�b�`�̐���������������
	if (flagCount == switchCount)
	{
		// �I�[�v���t���O��true��
		openFlag = true;
	}
}

/*
@fn �ǂ̕ǂ��ǂ̃X�C�b�`���m�F���邩�Z�b�g����֐�
@param	�ǂ̎�ނ�object�����肷��p��Tag
*/
void MoveWallBlock::SetCheckSwitchTag(Tag& _tag)
{

	// �Ȃ�̕ǂȂ̂����Q�Ƃ��ă`�F�b�N���ׂ��X�C�b�`���Z�b�g
	switch (_tag)
	{
		// �����̕ǂ�������
	case(Tag::FIRST_MOVE_WALL):
		checkTag = Tag::FIRST_SWITCH;
		break;

		// �����̕ǂ�������
	case(Tag::SECOND_MOVE_WALL):
		checkTag = Tag::SECOND_SWITCH;
		break;

		// �Q�[���N���A�O�̕ǂ�������
	case(Tag::CLEAR_SCENE_MOVE_WALL):
		checkTag = Tag::CLEAR_SCENE_SWITCH;
		break;
	}
}