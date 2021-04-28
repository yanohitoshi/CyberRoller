#include "SwitchBlock.h"
#include "Skeleton.h"
#include "ChangeColorMeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "BoxCollider.h"
#include "MainCameraObject.h"
#include "TutorialSwitchParticlEffect.h"
#include "TutorialSwitchOkEffect.h"
#include "SwitchEffectMakeManeger.h"
#include "FirstStageUI.h"
#include <string>


SwitchBlock::SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, MOVE_UP_SPEED(150.0f)
	, MOVE_DOWN_SPEED(-250.0f)
	, SHIFT_STOP_POSITION(40.0f)
	, ALL_CLEAR_COLOR(Vector3(1.0f, 1.0f, 0.5f))
	, ON_CLEAR(Vector3(0.1f, 0.1f, 1.0f))
	, OFF_CLEAR(Vector3(1.0f, 0.1f, 0.1f))
{
	//GameObject�����o�ϐ��̏�����
	position = _owner->GetPosition();
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	velocity = Vector3::Zero;
	initPosition = position;
	stopPoint = position.z - SHIFT_STOP_POSITION;
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new ChangeColorMeshComponent(this,false,true);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergyCube.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����߂�����p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::SwitchTag, GetOnCollisionFunc());
	AABB aabb = { Vector3(-55.0f,-55.0f,-40.0f),Vector3(55.0f,55.0f,55.0f) };
	boxCollider->SetObjectBox(aabb);

	// �t���O�̏�����
	tmpChangeColorFlag = false;
	changeColorFlag = false;
	pushStop = false;
	isOnPlayer = false;
	isHitPlayer = false;
	onFlag = false;
	isAvailableSwitch = true;

	// �`���[�g���A���p�̃X�C�b�`��������`���[�g���A���p�̃p�[�e�B�N����t�^
	if (tag == Tag::TUTORIAL_SWITCH)
	{
		new TutorialSwitchParticlEffect(Vector3(position.x,position.y,position.z + 250.0f),this);
		new TutorialSwitchOkEffect(Vector3(position.x, position.y, position.z + 250.0f), this);
	}

	// �X�C�b�`�p�̃G�t�F�N�g��t�^
	new SwitchEffectMakeManeger(this);

}

SwitchBlock::~SwitchBlock()
{
}

void SwitchBlock::UpdateGameObject(float _deltaTime)
{
	// �����蔻��p��world���AABB���擾
	aabb = boxCollider->GetWorldBox();

	// �X�C�b�`�̏�Ԃ��m�F
	ChackOnFlag(tag);

	// �O�̃t���[���ŐF�̕ϊ����N�������t���O��ۑ�
	tmpChangeColorFlag = changeColorFlag;

	// �|�W�V�������F��ύX����ʒu�����Ⴍ�v���C���[������Ă�����F�ύX�t���O��true��
	if (position.z <= stopPoint && isOnPlayer == true)
	{
		changeColorFlag = true;
	}
	else
	{
		changeColorFlag = false;
	}

	 // �O�̃t���[���ŐF���ύX����Ă��Ȃ�������
	if (changeColorFlag == true && tmpChangeColorFlag == false)
	{
		// �X�C�b�`�̗��p���\��Ԃ�������
		if (isAvailableSwitch == true)
		{
			// �X�C�b�`��OFF��������
			if (onFlag == false)
			{
				onFlag = true;
			}
		}
	}

	// �X�C�b�`�̏�Ԃ����ĐF��ύX
	if (onFlag == true && isAvailableSwitch == true)
	{
		// ON�̎�
		meshComponent->SetColor(ON_CLEAR);
	}
	else if (onFlag == false && isAvailableSwitch == true)
	{
		// OFF�̎�
		meshComponent->SetColor(OFF_CLEAR);
	}
	else if (isAvailableSwitch == false)
	{
		// ���̑S�ẴX�C�b�`��������Ă��鎞
		meshComponent->SetColor(ALL_CLEAR_COLOR);
	}
	
	// �X�C�b�`�̉�����
	// �v���C���[������Ă��Ȃ��Ă��������Ă��Ȃ�������
	if (isOnPlayer == false && isHitPlayer == false)
	{
		// �����̃|�W�V���������Ⴂ�ʒu�ɋ�����
		if (position.z < initPosition.z)
		{
			// �㏸���鑬�x����������
			velocity.z = MOVE_UP_SPEED;
		}
		else if (position.z >= initPosition.z) // �����|�W�V�����܂œ��B���Ă�����
		{
			// ���x��؂�
			velocity.z = 0.0f;
		}
	}
	else if (isOnPlayer == true) // �v���C���[������Ă�����
	{
		// ��~�t���O��false��������
		if (pushStop == false)
		{
			// ���~�̑��x����������
			velocity.z = MOVE_DOWN_SPEED;
		}
		else if (pushStop == true) // ��~�t���O��true��������
		{
			// ���x��؂�
			velocity.z = 0.0f;
		}
	}

	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;
	// �|�W�V�������X�V
	SetPosition(position);

	// �����蔻��n�t���O��������
	isOnPlayer = false;
	isHitPlayer = false;

}


void SwitchBlock::ChackOnFlag(Tag& _Tag)
{
	// ���ׂ�X�C�b�`�̉ϒ��z���ۑ����邽�߂̔z��
	std::vector<GameObject*> switches;

	// _Tag���g�p���Ē��ׂ�X�C�b�`��T��
	switches = GameObject::FindGameObject(_Tag);

	// �J�E���g�𐶐�
	int switchCount = 0;
	int flagCount = 0;
	for (auto itr : switches)
	{
		// �X�C�b�`�̐��𐔂���
		++switchCount;
		if (itr->GetSwitchFlag() == true)
		{
			// ON�ɂȂ��Ă���X�C�b�`�̐��𐔂���
			++flagCount;
		}
	}
	// �X�C�b�`�̑�����ON�ɂȂ��Ă���X�C�b�`�̑�����������������
	if (flagCount == switchCount)
	{
		// �X�C�b�`�𗘗p�s�ɂ���
		isAvailableSwitch = false;
	}

}

void SwitchBlock::OnCollision(const GameObject& _hitObject)
{
	// �q�b�g�����I�u�W�F�N�g���v���C���[��������
	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		// �v���C���[�Ƃ�Hit�t���O��true��
		isHitPlayer = true;

		// ��ɏ���Ă���t���O��true��
		isOnPlayer = true;
		// ��x��~�t���O��false��
		pushStop = false;
		// ������~�ʒu�ɂ�������
		if (position.z <= stopPoint)
		{
			// ��~�t���O��true��
			pushStop = true;
		}
	}
	// �q�b�g�����I�u�W�F�N�g����������������
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// �������̑��x����������
		Vector3 groundVel = _hitObject.GetVelocity();
		velocity.x = groundVel.x;
		velocity.y = groundVel.y;
	}

}

void SwitchBlock::PlayerFootOnCollision(const GameObject& _hitObject)
{
}
