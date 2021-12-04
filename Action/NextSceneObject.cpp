//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "NextSceneObject.h"
#include "MeshComponent.h"
#include "RenderingObjectManager.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "CrystalEffectManager.h"
#include "SoundEffectComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�I�u�W�F�N�g���ʗptag
@param	�v���C���[�̃|�C���^
@param	�V�[���̍Ō�̓����ǃI�u�W�F�N�g�̃|�C���^
*/
NextSceneObject::NextSceneObject(const Vector3& _pos, const Tag& _objectTag, PlayerObject* _playerObject, MoveWallBlock* _lastMoveWallBlock)
	: GameObject(false, _objectTag)
	, playerObject(_playerObject)
	, lastMoveWallBlock(_lastMoveWallBlock)
	, Angle(15.0f)
	, MoveSpeed(20.0f)
	, CalculationDrawEndPosition(3000.0f)
{

	//GameObject�����o�ϐ��̏�����
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
	firstPos = _pos;
	tag = _objectTag;
	state = Active;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	playClearSound = true;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Collection/model/SM_Big_Gems.gpmesh"));
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::CLEAR_POINT_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-5.0f,-5.0f,-5.0f),Vector3(5.0f,5.0f,15.0f) };
	boxCollider->SetObjectBox(aabb);

	// 4�F�̃G�t�F�N�g��t�^
	new CrystalEffectManager(this,CrystalColor::WHITE, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::RED, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::BLUE, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::GREEN, lastMoveWallBlock);

	soundEffectComponent = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Clear/stageClear.wav");
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
NextSceneObject::~NextSceneObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void NextSceneObject::UpdateGameObject(float _deltaTime)
{
	if (playerObject->GetClearFlag() == true)
	{
		// ���x�t�^
		velocity.z = MoveSpeed;
		
		// ��]����
		RotationProcess();

		// ������
		MovableProcess();

		// �J�����ɒ���������̂Ń|�W�V������n��
		mainCamera->SetLerpObjectPos(position);

		if (playClearSound)
		{
			soundEffectComponent->Play();
			playClearSound = false;
		}
	}
}

/*
@fn ��]�����֐�
*/
void NextSceneObject::RotationProcess()
{
	//Z�����w��p�x��]������
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

}

/*
@fn �������֐�
*/
void NextSceneObject::MovableProcess()
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
void NextSceneObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}