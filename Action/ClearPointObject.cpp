//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ClearPointObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "GameClearEffectManager.h"
#include "CrystalEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�I�u�W�F�N�g���ʗptag
@param	�v���C���[�̃|�C���^
@param	�V�[���̍Ō�̓����ǃI�u�W�F�N�g�̃|�C���^
*/
ClearPointObject::ClearPointObject(const Vector3& _pos, const Tag& _objectTag,PlayerObject* _playerObject, MoveWallBlock* _lastMoveWallBlock)
	: GameObject(false,_objectTag)
	, playerObject(_playerObject)
	, lastMoveWallBlock(_lastMoveWallBlock)
	, Angle(10.0f)
	, MoveSpeed(50.0f)
{

	//GameObject�����o�ϐ��̏�����
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
	tag = _objectTag;
	state = Active;
	velocity = Vector3(0.0f, 0.0f, 0.0f);

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/goods_model/SM_Gems_01a.gpmesh"));
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::CLEAR_POINT_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-5.0f,-5.0f,-5.0f),Vector3(5.0f,5.0f,15.0f) };
	boxCollider->SetObjectBox(aabb);

	playerObject = _playerObject;

	// �Q�[�����N���A�����Ƃ��ɏo���G�t�F�N�g���Ǘ�����N���X�𐶐�
	new GameClearEffectManager(this);

	// 4�F�̃G�t�F�N�g��t�^
	new CrystalEffectManager(this, CrystalColor::WHITE, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::RED, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::BLUE, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::GREEN, lastMoveWallBlock);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ClearPointObject::~ClearPointObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ClearPointObject::UpdateGameObject(float _deltaTime)
{
	if (playerObject->GetClearFlag() == true)
	{
		// ���x��t�^
		velocity.z = MoveSpeed;

		// ��]����
		RotationProcess();

		// ������
		MovableProcess();

		// �J�����ɒ���������̂Ń|�W�V������n��
		mainCamera->SetLerpObjectPos(position);

	}
}

/*
@fn ��]�����֐�
*/
void ClearPointObject::RotationProcess()
{
	//Z����10�x��]������
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
@fn �������֐�
*/
void ClearPointObject::MovableProcess()
{
	// �|�W�V�����ɑ��x�𑫂�
	position += velocity;
	// �|�W�V�������X�V
	SetPosition(position);
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void ClearPointObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}