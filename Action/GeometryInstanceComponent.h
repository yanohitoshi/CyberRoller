#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Component.h"
#include <string>
#include "GeometryInstanceManager.h"

/// <summary>
/// �W�I���g���C���X�^���X�̂��߂̃R���|�[�l���g
/// </summary>
class GeometryInstanceComponent : public Component
{
public:
	/// <summary>
	/// �����o�[�ϐ��̏������ƃW�I���g���C���X�^���X�}�l�[�W���[�Ƀ��b�V����o�^
	/// </summary>
	/// <param name="_owner">���̃R���|�[�l���g�̏��L�A�N�^�[</param>
	/// <param name="_mesh">�o�^���������b�V��</param>
	/// <param name="_type">�W�I���g���C���X�^���X�̎��</param>
	/// <param name="_maxInstanceNum">�ő�`�搔</param>
	GeometryInstanceComponent(class GameObject* _owner,class Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum = 200);

	/// <summary>
	/// �W�I���g���C���X�^���X�}�l�[�W���[�ɃA�N�^�[�ɕ`��\�ȃA�N�^�[��ǉ�
	/// </summary>
	void AddGeometryInstanceManager();

	/// <summary>
	/// �W�I���g���C���X�^���X�}�l�[�W���[����A�N�^�[���폜
	/// </summary>
	void RemoveGeometryInstanceManager();

	/// <summary>
	/// �W�I���g���C���X�^���X�}�l�[�W���[���烁�b�V���̃|�C���^��Ԃ�
	/// </summary>
	/// <returns>���b�V���̃|�C���^</returns>
	class Mesh* GetMesh()const;

private:
	//�W�I���g���C���X�^���X�}�l�[�W���[�̃|�C���^
	class GeometryInstanceManager* mGeometryInstanceManager;
	//�W�I���g���C���X�^���X�̎��
	GeometryInstanceType mGeometryInstanceType;
	//���b�V���̃|�C���^
	class Mesh* mMesh;
};

