#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Component.h"
#include <string>
#include "GeometryInstanceManager.h"

/*
@file GeometryInstanceComponent.h
@brief �W�I���g���C���X�^���X�̂��߂̃R���|�[�l���g
*/
class GeometryInstanceComponent : public Component
{
public:

	/*
	@fn �R���X�g���N�^
	@brief �����o�[�ϐ��̏������ƃW�I���g���C���X�^���X�}�l�[�W���[�Ƀ��b�V����o�^
	@param _owner ���̃R���|�[�l���g�̏��L�I�u�W�F�N�g
	@param _mesh �o�^���������b�V��
	@param _type �W�I���g���C���X�^���X�̎��
	@param _maxInstanceNum �ő�`�搔
	*/
	GeometryInstanceComponent(class GameObject* _owner,class Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum = 200);

	/*
	@brief �W�I���g���C���X�^���X�}�l�[�W���[�ɃA�N�^�[�ɕ`��\�ȃA�N�^�[��ǉ�
	*/
	void AddGeometryInstanceManager();

	/*
	@brief �W�I���g���C���X�^���X�}�l�[�W���[����A�N�^�[���폜
	*/
	void RemoveGeometryInstanceManager();

	/*
	@brief �W�I���g���C���X�^���X�}�l�[�W���[���烁�b�V���̃|�C���^��Ԃ�
	@return ���b�V���̃|�C���^
	*/
	class Mesh* GetMesh()const;

private:

	//�W�I���g���C���X�^���X�}�l�[�W���[�̃|�C���^
	class GeometryInstanceManager* geometryInstanceManager;
	//�W�I���g���C���X�^���X�̎��
	GeometryInstanceType geometryInstanceType;
	//���b�V���̃|�C���^
	class Mesh* mesh;
};

