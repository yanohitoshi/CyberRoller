#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file SkyBoxObject.h
@brief SkyBoxObject管理クラス
*/
class SkyBoxObject : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	SkyBoxObject(bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~SkyBoxObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn キューブマップComponentのgetter
	@return	cubeMapComp 使用しているキューブマップComponentを返す
	*/
	class CubeMapComponent* GetCubeMapComp() { return cubeMapComp; }

private:

	// キューブマップComponentクラスのポインタ
	class CubeMapComponent* cubeMapComp;
};