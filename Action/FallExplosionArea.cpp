//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FallExplosionArea.h"
#include "FallExplosionObject.h"
#include "BoxCollider.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	�I�u�W�F�N�g���ʗptag
@param	�G���A�̍L��
@param	�������̐�
*/
FallExplosionArea::FallExplosionArea(const Vector3& _pos, const Tag _objectTag,Vector3& _area, int _quantity)
	: GameObject(false, _objectTag)
	, area(Vector3::Zero)
{
	position = _pos;
	SetPosition(position);
	quantity = _quantity;
	isFallStart = false;
	area = _area;
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::FALL_BOMB_AREA_TAG, GetOnCollisionFunc());
	AABB aabb = { _area * -1.0f,_area };
	boxCollider->SetObjectBox(aabb);

	fallExplosionObjects.resize(quantity);

	// ���̃G���A�ɍ~����������𐶐�
	for (int i = 0; i < quantity; i++)
	{
		fallExplosionObjects[i] = new FallExplosionObject(this, position, Tag::FALL_BOMB);
	}

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
FallExplosionArea::~FallExplosionArea()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void FallExplosionArea::UpdateGameObject(float _deltaTime)
{
	// �����~���Ԃ�������~��Ȃ���ԂɕύX
	if (isFallStart)
	{
		isFallStart = false;
	}
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	�����蔻��^�O
*/
void FallExplosionArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �v���C���[�ɓ��������甚�������~���ԂɕύX
	if (_physicsTag == PhysicsTag::PLAYER_TAG)
	{
		isFallStart = true;
	}
}