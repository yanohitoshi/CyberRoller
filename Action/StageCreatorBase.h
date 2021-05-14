#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

// 前置宣言
class PlayerObject;


enum StagePartsName
{
	// 縦長壁パーツ
	PORTRAIT_WALL_PARTS = 1,
	// 横長壁パーツ
	LANDSCAPE_WALL_PARTS = 2,
	// リスポーンポイントパーツ
	RESPOWN_POINT_PARTS = 3,
	// 棘パネルパーツ
	NEEDLE_PARTS = 16,
	// ステージクリアオブジェクトパーツ
	CLEAR_OBJECT_PARTS = 20,
	// 最初の区画スイッチパーツ
	FIRST_SWITCH_PARTS = 21,
	// ジャンプスイッチパーツ
	JUMP_SWITCH_PARTS = 40,
	// 最初の区画の動く壁パーツ
	FIRST_MOVE_WALL_PARTS = 41,

	// レイヤーごとのブロックパーツ名
	// ※Tiled Map Editorを使用してJSONファイルを制作する際にレイヤー別にブロックのタイルマップの色を変えているため
	LAYER1_BLOCK_PARTS = 79, // レイヤー1
	LAYER2_BLOCK_PARTS = 78, // レイヤー2
	LAYER3_BLOCK_PARTS = 77, // レイヤー3
	LAYER4_BLOCK_PARTS = 76, // レイヤー4
	LAYER5_BLOCK_PARTS = 75, // レイヤー5
	LAYER6_BLOCK_PARTS = 74, // レイヤー6
	LAYER7_BLOCK_PARTS = 73, // レイヤー7
	LAYER8_BLOCK_PARTS = 72, // レイヤー8
	LAYER9_BLOCK_PARTS = 71, // レイヤー9
	LAYER10_BLOCK_PARTS = 70, // レイヤー10
	LAYER11_BLOCK_PARTS = 69, // レイヤー11
	LAYER12_BLOCK_PARTS = 68, // レイヤー12
	LAYER13_BLOCK_PARTS = 67, // レイヤー13
	LAYER14_BLOCK_PARTS = 66, // レイヤー14
	LAYER15_BLOCK_PARTS = 65, // レイヤー15
	LAYER16_BLOCK_PARTS = 64, // レイヤー16
	LAYER17_BLOCK_PARTS = 63, // レイヤー17


};
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

	// プレイヤーを見たいclassにプレイヤーのポインタを渡すための変数
	PlayerObject* playerObject;

};

