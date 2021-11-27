//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GeometryInstanceComponent.h"
#include "RenderingObjectManager.h"
#include "Game.h"

/*
@fn �R���X�g���N�^
@brief �����o�[�ϐ��̏������ƃW�I���g���C���X�^���X�}�l�[�W���[�Ƀ��b�V����o�^
@param _owner ���̃R���|�[�l���g�̏��L�I�u�W�F�N�g
@param _mesh �o�^���������b�V��
@param _type �W�I���g���C���X�^���X�̎��
@param _maxInstanceNum �ő�`�搔
*/
GeometryInstanceComponent::GeometryInstanceComponent(GameObject* _owner, Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum)
	:Component(_owner)
	, geometryInstanceManager(RENDERING_OBJECT_MANAGER->GetGeometryInstanceManager())
	, geometryInstanceType(_type)
	, mesh(_mesh)

{
	//�W�I���g���C���X�^���X�}�l�[�W���[�Ƀ��b�V����o�^
	geometryInstanceManager->SetInstanceMesh(_mesh, _maxInstanceNum, _type);
}

/*
@brief �W�I���g���C���X�^���X�}�l�[�W���[�ɃA�N�^�[�ɕ`��\�ȃA�N�^�[��ǉ�
*/
void GeometryInstanceComponent::AddGeometryInstanceManager()
{
	//�W�I���g���C���X�^���X�}�l�[�W���[�ɕ`�悷��A�N�^�[��ǉ�
	geometryInstanceManager->AddGeometryInstanceGameObject(GetOwner(), geometryInstanceType);
}

/*
@brief �W�I���g���C���X�^���X�}�l�[�W���[����A�N�^�[���폜
*/
void GeometryInstanceComponent::RemoveGeometryInstanceManager()
{
	// �W�I���g���C���X�^���X�}�l�[�W���[����A�N�^�[���폜
	geometryInstanceManager->RemoveGeometryInstanceGameObject(GetOwner(), geometryInstanceType);
}

/*
@brief �W�I���g���C���X�^���X�}�l�[�W���[���烁�b�V���̃|�C���^��Ԃ�
@return ���b�V���̃|�C���^
*/
Mesh* GeometryInstanceComponent::GetMesh() const
{
	//�W�I���g���C���X�^���X�}�l�[�W���[���烁�b�V����Ԃ�
	return geometryInstanceManager->GetMesh(geometryInstanceType);
}