#include "MoveWallBlock.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Skeleton.h"
#include <string>
#include "BoxCollider.h"
#include "SandSmokeMakeManeger.h"
#include "MainCameraObject.h"
#include "FirstStageUI.h"
#include "PlayerObject.h"


MoveWallBlock::MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, float _speed, Vector3 _stopPos)
	: GameObject(false, _objectTag)
	, moveSpeed(_speed)
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
	isFlinchToPlayer = true;
	isPushBackToCamera = true;
	SetChackSwitchTag(tag);

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this,false,false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/moveWall_model/moveWallBox.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::WALL_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	// �y���G�t�F�N�g�̕t�^
	new SandSmokeMakeManeger(this);

}

MoveWallBlock::~MoveWallBlock()
{
}


void MoveWallBlock::UpdateGameObject(float _deltaTime)
{
	// ���[���h�{�b�N�X�̍X�V
	aabb = boxCollider->GetWorldBox();

	// �Ώۂ̃X�C�b�`�̏�Ԃ��`�F�b�N
	ChackSwitch(chackTag);

	// �I�[�v���t���O��true��������
	if (openFlag == true)
	{
		OpenWall(_deltaTime);
	}

	// �|�W�V�����̍X�V
	SetPosition(position);
}

void MoveWallBlock::OpenWall(float _deltaTime)
{
	// �ړ����x��t�^
	velocity.z = moveSpeed;
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

void MoveWallBlock::ChackSwitch(Tag& _tag)
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

void MoveWallBlock::SetChackSwitchTag(Tag& _tag)
{

	// �Ȃ�̕ǂȂ̂����Q�Ƃ��ă`�F�b�N���ׂ��X�C�b�`���Z�b�g
	switch (_tag)
	{
		// �����̕ǂ�������
	case(Tag::FIRST_MOVE_WALL):
		chackTag = Tag::FIRST_SWITCH;
		break;

		// �����̕ǂ�������
	case(Tag::SECOND_MOVE_WALL):
		chackTag = Tag::SECOND_SWITCH;
		break;

		// �Q�[���N���A�O�̕ǂ�������
	case(Tag::CLEAR_SCENE_MOVE_WALL):
		chackTag = Tag::CLEAR_SCENE_SWITCH;
		break;
	}
}


