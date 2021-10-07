#include "SkyBoxObject.h"
#include "CubeMapComponent.h"
#include "Renderer.h"

SkyBoxObject::SkyBoxObject(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
{
	// キューブマップコンポーネントを生成
	cubeMapComp = new CubeMapComponent(this);
	// レンダラーにActiveなキューブマップとしてポインタを渡す
	RENDERER->SetActiveSkyBox(cubeMapComp);
	// texture生成
	cubeMapComp->CreateTexture("Assets/sprite/night/");
}


SkyBoxObject::~SkyBoxObject()
{

}

void SkyBoxObject::UpdateGameObject(float _deltaTime)
{
}
