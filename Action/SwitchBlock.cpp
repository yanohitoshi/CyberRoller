//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
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

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param	�`���[�g���A���p�X�C�b�`���ǂ����t���O
*/
SwitchBlock::SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag,bool _isTutorial)
	: GameObject(false, _objectTag)
	, MoveUpSpeed(150.0f)
	, MoveDownSpeed(-250.0f)
	, ShiftStopPosition(40.0f)
	, AllClearColer(Vector3(1.0f, 1.0f, 0.5f))
	, OnColor(Vector3(0.1f, 0.1f, 1.0f))
	, OffColor(Vector3(1.0f, 0.1f, 0.1f))
	,isTutorialSwitch(_isTutorial)
{
	//GameObject�����o�ϐ��̏�����
	position = _owner->GetPosition();
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	velocity = Vector3::Zero;
	initPosition = position;
	stopPoint = position.z - ShiftStopPosition;
	isPushBackToPlayer = true;
	isSendVelocityToPlayer = true;
	isCheckGroundToPlayer = true;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new ChangeColorMeshComponent(this,false,true);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/switch_model/S_EnergyCube.gpmesh"));

	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();
	//�����߂�����p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::SWITCH_TAG, GetOnCollisionFunc());
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
	if (isTutorialSwitch)
	{
		new TutorialSwitchParticlEffect(Vector3(position.x,position.y,position.z + 250.0f),this);
		new TutorialSwitchOkEffect(Vector3(position.x, position.y, position.z + 250.0f), this);
	}

	// �X�C�b�`�p�̃G�t�F�N�g��t�^
	new SwitchEffectMakeManeger(this);

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
SwitchBlock::~SwitchBlock()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void SwitchBlock::UpdateGameObject(float _deltaTime)
{
	// �����蔻��p��world���AABB���擾
	aabb = boxCollider->GetWorldBox();

	// �X�C�b�`�̏�Ԃ��m�F
	CheckOnFlag(tag);
	// �F�ύX����
	ColorChangeProcess();
	// ������
	MovableProcess();

	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;
	// �|�W�V�������X�V
	SetPosition(position);

	// �����蔻��n�t���O��������
	isOnPlayer = false;
	isHitPlayer = false;

}

/*
@fn �������֐�
*/
void SwitchBlock::MovableProcess()
{
	// �X�C�b�`�̉�����
	// �v���C���[������Ă��Ȃ��Ă��������Ă��Ȃ�������
	if (isOnPlayer == false && isHitPlayer == false)
	{
		// �����̃|�W�V���������Ⴂ�ʒu�ɋ�����
		if (position.z < initPosition.z)
		{
			// �㏸���鑬�x����������
			velocity.z = MoveUpSpeed;
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
			velocity.z = MoveDownSpeed;
		}
		else if (pushStop == true) // ��~�t���O��true��������
		{
			// ���x��؂�
			velocity.z = 0.0f;
		}
	}
}

/*
@fn �F�ύX����
*/
void SwitchBlock::ColorChangeProcess()
{
	// �O�̃t���[���ŐF�̕ϊ����N�������t���O��ۑ�
	tmpChangeColorFlag = changeColorFlag;

	// �|�W�V�������F��ύX����ʒu�����Ⴍ�v���C���[������Ă�����F�ύX�t���O��true��
	if (position.z <= stopPoint && isOnPlayer == true)
	{
		changeColorFlag = true;
	}
	else
	{
		// ���̑��̏ꍇ�J���[�`�F���W�t���O��false��
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

	SetColorProcess();
}

/*
@fn �F�Z�b�g����
*/
void SwitchBlock::SetColorProcess()
{
	// �X�C�b�`�̏�Ԃ����ĐF��ύX
	if (onFlag == true && isAvailableSwitch == true)
	{
		// ON�̎�
		meshComponent->SetColor(OnColor);
	}
	else if (onFlag == false && isAvailableSwitch == true)
	{
		// OFF�̎�
		meshComponent->SetColor(OffColor);
	}
	else if (isAvailableSwitch == false)
	{
		// ���̑S�ẴX�C�b�`��������Ă��鎞
		meshComponent->SetColor(AllClearColer);
		luminance = 0.2f;
	}
}

/*
@fn �^�O���Ƃ̃X�C�b�`�̏�ԃ`�F�b�N�֐�
@param _Tag �`�F�b�N����X�C�b�`��Tag
*/
void SwitchBlock::CheckOnFlag(Tag& _Tag)
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

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	�������Ɛڂ��Ă��鎞�ɂ��̑��x�����炤���߂�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void SwitchBlock::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_physicsTag == PhysicsTag::GROUND_CHECK_TAG)
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