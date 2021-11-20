//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SkyBoxObject.h"
#include "CubeMapComponent.h"
#include "Renderer.h"

/*
@fn �R���X�g���N�^
@param	�ė��p���邩�t���O
@param	�I�u�W�F�N�g���ʗptag
*/
SkyBoxObject::SkyBoxObject(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
{
	// �L���[�u�}�b�v�R���|�[�l���g�𐶐�
	cubeMapComp = new CubeMapComponent(this);
	// �����_���[��Active�ȃL���[�u�}�b�v�Ƃ��ă|�C���^��n��
	RENDERER->SetActiveSkyBox(cubeMapComp);
	// texture����
	cubeMapComp->CreateTexture("Assets/sprite/skyBox/night/");
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
SkyBoxObject::~SkyBoxObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void SkyBoxObject::UpdateGameObject(float _deltaTime)
{
}