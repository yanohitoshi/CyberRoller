//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SkyBoxObject.h"
#include "CubeMapComponent.h"
#include "Renderer.h"

/*
@fn コンストラクタ
@param	再利用するかフラグ
@param	オブジェクト判別用tag
*/
SkyBoxObject::SkyBoxObject(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
{
	// キューブマップコンポーネントを生成
	cubeMapComp = new CubeMapComponent(this);
	// レンダラーにActiveなキューブマップとしてポインタを渡す
	RENDERER->SetActiveSkyBox(cubeMapComp);
	// texture生成
	cubeMapComp->CreateTexture("Assets/sprite/skyBox/night/");
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
SkyBoxObject::~SkyBoxObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void SkyBoxObject::UpdateGameObject(float _deltaTime)
{
}