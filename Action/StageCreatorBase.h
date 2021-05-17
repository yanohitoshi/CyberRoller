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
	NEEDLE_PARTS = 4,

	// ステージクリアオブジェクトパーツ
	CLEAR_OBJECT_PARTS = 20,

	// 第一区画のスイッチパーツ
	FIRST_SWITCH_PARTS = 21,
	// 第二区画のスイッチパーツ
	SECOND_SWITCH_PARTS = 22,
	// 第三区画のスイッチパーツ
	THIRD_SWITCH_PARTS = 23,

	// ジャンプスイッチパーツ
	JUMP_SWITCH_PARTS = 40,

	// 第一区画の動く壁パーツ
	FIRST_MOVE_WALL_PARTS = 41,
	// 第二区画の動く壁パーツ
	SECOND_MOVE_WALL_PARTS = 42,
	// 第三区画の動く壁パーツ
	THIRD_MOVE_WALL_PARTS = 43,

	// プレイヤー
	PLAYER_PARTS = 19,

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

	// 動く壁のポジションを少しずらす定数
	// Y軸は中心のずらすため・Z軸は少し埋まった状態で生成したいため
	const float ShiftMoveWallY;
	const float ShiftMoveWallZ;

	// 動く壁の速度定数
	const float MoveWallSpeed;

	//配置するオブジェクトの間隔。サイズ
	const float Offset;

	// ブロックオブジェクトのサイズ定数
	const Vector3 BlockSize;
	// スイッチオブジェクトのサイズ定数
	const Vector3 SwitchBaseSize;
	// ジャンプスイッチオブジェクトのサイズ定数
	const Vector3 JumpSwitchSize;
	// ニードルオブジェクトのサイズ定数
	const Vector3 NeedlePanelSize;
	// 縦長壁オブジェクトのサイズ定数
	const Vector3 PortraitWallBlockSize;
	// 横長壁オブジェクトのサイズ定数
	const Vector3 LandscapeWallBlockSize;
	// 大きい動く壁オブジェクトのサイズ定数
	const Vector3 BigMoveWallSize;
	// 小さい動く壁オブジェクトのサイズ定数
	const Vector3 SmallMoveWallSize;
	// リスポーンポイントオブジェクトの当たり判定サイズ（AABB）定数
	const AABB RespawnBox;

	// スイッチのポジションは他のオブジェクトと違いずらす必要があるので
	// そのために用いる定数
	const float ShiftSwitchPositionZ;

	// レイヤー数の最大値
	const int MaxLayer;

	// レイヤーごとに割り当てるZ軸の値を格納する配列
	float ObjectPositionZ[17];



};

