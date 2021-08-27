#include "SkyBoxObject.h"
#include "CubeMapComponent.h"
#include "Renderer.h"

SkyBoxObject::SkyBoxObject(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
{
	cubeMapComp = new CubeMapComponent(this);
	RENDERER->SetActiveSkyBox(cubeMapComp);
	cubeMapComp->CreateTexture("Assets/sprite/night/");
}


SkyBoxObject::~SkyBoxObject()
{

}

void SkyBoxObject::UpdateGameObject(float _deltaTime)
{
}
