#include "GeometryInstanceComponent.h"
#include "Renderer.h"
#include "Game.h"

/// <summary>
/// �����o�[�ϐ��̏������ƃW�I���g���C���X�^���X�}�l�[�W���[�Ƀ��b�V����o�^
/// </summary>
/// <param name="_owner">���̃R���|�[�l���g�̏��L�A�N�^�[</param>
/// <param name="_mesh">�o�^���������b�V��</param>
/// <param name="_type">�W�I���g���C���X�^���X�̎��</param>
/// <param name="_maxInstanceNum">�ő�`�搔</param>
GeometryInstanceComponent::GeometryInstanceComponent(GameObject* _owner, Mesh* _mesh, GeometryInstanceType _type, const unsigned int _maxInstanceNum)
	:Component(_owner)
	,mGeometryInstanceManager(RENDERER->GetGeometryInstanceManager())
	,mGeometryInstanceType(_type)
	,mMesh(_mesh)

{
	//�W�I���g���C���X�^���X�}�l�[�W���[�Ƀ��b�V����o�^
	mGeometryInstanceManager->SetInstanceMesh(_mesh, _maxInstanceNum, _type);
}

void GeometryInstanceComponent::AddGeometryInstanceManager()
{
	//�W�I���g���C���X�^���X�}�l�[�W���[�ɕ`�悷��A�N�^�[��ǉ�
	mGeometryInstanceManager->AddGeometryInstanceActor(GetOwner(), mGeometryInstanceType);
}

void GeometryInstanceComponent::RemoveGeometryInstanceManager()
{
	//�W�I���g���C���X�^���X�}�l�[�W���[����A�N�^�[���폜
	//mGeometryInstanceManager->RemoveGeometryInstanceActor(GetOwner(), mGeometryInstanceType);
	////�Q�[���̏�Ԃ��I���łȂ��Ȃ�
	//if (Game::GetState() != GameState::EQuit)
	//{
	//}
}

Mesh* GeometryInstanceComponent::GetMesh() const
{
	//�W�I���g���C���X�^���X�}�l�[�W���[���烁�b�V����Ԃ�
	return mGeometryInstanceManager->GetMesh(mGeometryInstanceType);
}
