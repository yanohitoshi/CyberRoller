#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file StageCreatorBase.h
@brief ステージ生成classの基底クラス
*/
class StageCreatorBase :
    public GameObject
{
public:
	/*
	@fn コンストラクタ
	@brief  objectの生成を行う
	@param	_reUseGameObject 再利用するかどうかフラグ
	@param	_objectTag オブジェクト判別用Tag
	*/
	StageCreatorBase(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~StageCreatorBase()override;

protected:
	/*
	@fn Jsonファイルを読み込みコンテナ型に格納する
	@param _mapDate 格納させたいコンテナへのアドレス
	@param _fileName Jsonファイルアドレス
	@param _layerName Jsonファイル内のレイヤーアドレス
	@return false=失敗
	*/
	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _filename, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName);


};

