#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <cstdint>

// �N���X�̑O���錾
class GameObject;

/*
 @file Component.h
 @brief �R���|�[�l���g�̊��N���X
*/
class Component
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	Component(GameObject* _owner,int _updateOrder = 100);

	/*
	@fn �f�X�g���N�^
	@brief  component�̍폜���s��
	*/
	virtual ~Component();

	/*
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime);

	/*
	@brief	���͏���
	@param	InputState�\����
	*/
	virtual void ProcessInput(const struct InputState& _state) {}

	/*
	@brief	Transform�̃��[���h�ϊ�
	*/
	virtual void OnUpdateWorldTransform() {}

protected:

	//�A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	GameObject* owner;			
	// �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	int updateOrder;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@return �X�V����
	*/
	int GetUpdateOder() const { return updateOrder; }

	/*
	@return �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�ւ̃|�C���^
	*/
	GameObject* GetOwner() const { return owner; };
};

