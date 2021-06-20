#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PhysicsWorld.h"
#include "ColliderComponent.h"

class MainCameraObject;

/*
 @file LineSegmentCollider.h
 @brief �����̓����蔻��N���X�i�������j
*/
class LineSegmentCollider : public ColliderComponent
{
public:

	/*
	@brief	�R���X�g���N�^
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	���̃I�u�W�F�N�g�Ɠ����������ɌĂ΂��֐��|�C���^(GetOnCollisionFunc���Ă�)
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	@param	�����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
	*/
	LineSegmentCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag,onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/*
	@brief	�f�X�g���N�^
	*/
	virtual ~LineSegmentCollider();

	/*
	@brief	Transform�̃��[���h�ϊ�
	*/
	void OnUpdateWorldTransform() override;


private:

	//�I�u�W�F�N�g�ɐݒ肷��p�̐����i���S���I�u�W�F�N�g�̒��S�ɂ���j
	LineSegment objectLineSegment;

	//�����蔻�肷��Ƃ��Ɏg�������i���S�����[���h���W�̒��S�ɂ���j
	LineSegment worldLineSegment;

	// �l
	float value;

	// ���������ꏊ
	float contactPoint;

	// �O���x�N�g��
	Vector3 forwardVec;

	// hit�����Ԋu
	float interval;

	// �Փ˂����ꏊ
	Vector3 hitPoint;

	// �Փ˂����ꏊ
	Vector3 point;

	// �g�p����J�����̃|�C���^
	MainCameraObject* mainCamera;

public: // �Q�b�^�[�Z�b�^�[

	/*
	@brief	�����蔻��Ɏg�������̐ݒ�
	@param	�I�u�W�F�N�g�̑傫���ɍ��킹�������̍\����
	*/
	void SetObjectLineSegment(const LineSegment& _lineSegment) { objectLineSegment = _lineSegment; }
	
	/*
	@brief	�l(�����̒���)���Z�b�g����֐�(����Ȃ���������Ȃ��ł��c)
	@param	_value �Z�b�g����l
	*/
	void Setvalue(const float& _value) { value = _value; }
	
	/*
	@brief	�O���x�N�g�����Z�b�g����֐�
	@param	_forward �Z�b�g����O���x�N�g��
	*/
	void SetforwardVector(const Vector3& _forward) { forwardVec = _forward; }

	/*
	@brief	�����蔻�莞�Ɏg�����[���h��Ԃł̐���Vector���擾����
	@return ���S�����[���h���W�ɍ��킹������Vector
	*/
	LineSegment GetWorldLineSegment() const { return worldLineSegment; }
	
	/*
	@brief	���������ꏊ�𓾂�getter
	@return ���������ꏊ�̏��(float)
	*/
	float GetContactPoint(){ return contactPoint; }

	/*
	@brief	�����̊Ԋu���Z�b�g����֐�
	@param	_interval �Z�b�g��������̊Ԋu(float)
	*/
	void SetInterval(const float& _interval) { interval = _interval; }
	
	/*
	@brief	�����̊Ԋu�𓾂�getter
	@return �����̊Ԋu�̏��(float)
	*/
	float GetInterval() const { return interval; }
	
	/*
	@brief	���������ꏊ���Z�b�g����֐�
	@param	_interval �Z�b�g���铖�������ꏊ(Vector3)
	*/
	void SetHitPointVector(const Vector3& _hitPoint) { hitPoint = _hitPoint; }
	
	/*
	@brief	���������ꏊ�𓾂�getter(Vector3)
	@return ���������ꏊ�̏��(Vector3)
	*/
	Vector3 GetHitPointVector()const { return hitPoint; }

};

