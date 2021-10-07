#include "SkyBoxObject.h"
#include "CubeMapComponent.h"
#include "Renderer.h"

SkyBoxObject::SkyBoxObject(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
{
	// �L���[�u�}�b�v�R���|�[�l���g�𐶐�
	cubeMapComp = new CubeMapComponent(this);
	// �����_���[��Active�ȃL���[�u�}�b�v�Ƃ��ă|�C���^��n��
	RENDERER->SetActiveSkyBox(cubeMapComp);
	// texture����
	cubeMapComp->CreateTexture("Assets/sprite/night/");
}


SkyBoxObject::~SkyBoxObject()
{

}

void SkyBoxObject::UpdateGameObject(float _deltaTime)
{
}
