#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>
#include <unordered_map>
#include "MoveBlockObject.h"
#include "EnemyObjectBase.h"
#include "PushBoxObject.h"

// 前置宣言
class PlayerObject;
class MoveWallBlock;
class CollectionObject;
enum class CollectionTag;

/*
@enum　ステージを生成するに当たって使用するパーツの名前
*/
enum StagePartsName
{
	// 壊れるブロックパーツ
	BREAK_BLOCK_PARTS = 59,

	// 爆発物パーツ
	BOMB_PARTS = 60,

	// 右寄せのパワーセルライトパーツ
	POWERCELLS_LIGHT_PARTS_RIGHT = 1,
	// 左寄せのパワーセルライトパーツ
	POWERCELLS_LIGHT_PARTS_LEFT = 2,

	// リスポーンポイントパーツ
	RESPOWN_POINT_PARTS = 18,

	// 棘パネルパーツ
	NEEDLE_PARTS = 6,

	// ステージクリアオブジェクトパーツ
	CLEAR_OBJECT_PARTS = 20,

	// 第一区画のスイッチパーツ
	FIRST_SWITCH_PARTS = 21,
	// 第二区画のスイッチパーツ
	SECOND_SWITCH_PARTS = 22,
	// 第三区画のスイッチパーツ
	THIRD_SWITCH_PARTS = 23,
	
	// 最初右に動くblockパーツ
	RIGHT_MOVE_BLOCK_PARTS = 24,
	// 最初左に動くblockパーツ
	LEFT_MOVE_BLOCK_PARTS = 25,

	// ジャンプスイッチパーツ
	JUMP_SWITCH_PARTS = 7,

	// 第一区画の動く壁パーツ
	FIRST_MOVE_WALL_PARTS = 41,
	// 第二区画の動く壁パーツ
	SECOND_MOVE_WALL_PARTS = 42,
	// 第三区画の動く壁パーツ
	THIRD_MOVE_WALL_PARTS = 43,

	// 動かない敵
	NORMAL_ENEMY_PARTS = 44,
	// 最初右方向に移動する敵
	RIGHT_MOVE_ENEMY_PARTS = 45,
	// 最初左方向に移動する敵
	LEFT_MOVE_ENEMY_PARTS = 46,
	// 追跡する敵
	TRACKING_ENEMY_PARTS = 47,

	// 1番目の収集物パーツ
	COLLECTION_FIRST = 3,
	// 2番目の収集物パーツ
	COLLECTION_SECOND = 4,
	// 3番目の収集物パーツ
	COLLECTION_THIRD = 5,

	// プレイヤー
	PLAYER_PARTS = 19,

	// レイヤーごとのブロックパーツ名
	// ※Tiled Map Editorを使用してJSONファイルを制作する際にレイヤー別にブロックのタイルマップの色を変えているため
	LAYER1_BLOCK_PARTS = 61, // レイヤー1
	LAYER2_BLOCK_PARTS = 62, // レイヤー2
	LAYER3_BLOCK_PARTS = 63, // レイヤー3
	LAYER4_BLOCK_PARTS = 64, // レイヤー4
	LAYER5_BLOCK_PARTS = 65, // レイヤー5
	LAYER6_BLOCK_PARTS = 66, // レイヤー6
	LAYER7_BLOCK_PARTS = 67, // レイヤー7
	LAYER8_BLOCK_PARTS = 68, // レイヤー8
	LAYER9_BLOCK_PARTS = 69, // レイヤー9
	LAYER10_BLOCK_PARTS = 70, // レイヤー10
	LAYER11_BLOCK_PARTS = 71, // レイヤー11
	LAYER12_BLOCK_PARTS = 72, // レイヤー12
	LAYER13_BLOCK_PARTS = 73, // レイヤー13
	LAYER14_BLOCK_PARTS = 74, // レイヤー14
	LAYER15_BLOCK_PARTS = 75, // レイヤー15
	LAYER16_BLOCK_PARTS = 76, // レイヤー16
	LAYER17_BLOCK_PARTS = 77, // レイヤー17
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
	@brief  マップデータの削除を行う
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

	/*
	@fn プレイヤーを生産する関数
	@brief  プレイヤー用マップデータを用いてプレイヤーを生産する
	@param	_data マップデータ
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void ProductionPlayer(int _data, int _indexX, int _indexY);

	/*
	@fn 動く床のデータ構造体を生成する関数
	@param  どれくらいの距離動くのか
	@param　どの方向に動くのか
	@param　速度
	@param　どの方向に動くのか判別するためのタグ
	*/
	void SetMoveBlockData(const float _distance, const Vector3 _direction, const float _speed,const Vector3 _objectSize,MoveDirectionTag _moveTag);
	

	// 動く床クラスにデータを渡すための変数
	MoveBlockData moveBlockData;

	/*
	@fn プッシュボードのデータ構造体を生成する関数
	@param  どれくらいの距離動くのか
	@param　どの方向に動くのか
	@param　速度
	@param　どの方向に動くのか判別するためのタグ
	*/
	void SetPushBoxData(const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed, MoveDirectionTag _moveTag);

	// プッシュボード床クラスにデータを渡すための変数
	PushBoxData pushBoxData;

	/*
	@fn 動く敵のデータ構造体を生成する関数
	@param　速度
	@param　どの方向に動くのか
	@param  どれくらいの距離動くのか
	@param　どの方向に動くのか判別するためのタグ
	*/
	void SetMoveEnemyData(const float _speed, const Vector3 _direction, const float _distance, MoveEnemyTag _moveTag);
	
	// 動く敵クラスにデータを渡すための変数
	MoveEnemyData moveEnemyData;

	// プレイヤーを見たいclassにプレイヤーのポインタを渡すための変数
	PlayerObject* playerObject;

	// そのシーンでの最後の動く壁のポインタ
	// クリアオブジェクトに渡す(エフェクトを発生させるトリガーに使用するため)
	MoveWallBlock* lastMoveWallBlock;


	CollectionObject* firstCollectionObject;
	CollectionObject* secondCollectionObject;
	CollectionObject* thirdCollectionObject;

	// 動く壁のポジションを少しずらす定数
	// Y軸は中心のずらすため・Z軸は少し埋まった状態で生成したいため
	const float ShiftMoveWallY;
	const float ShiftMoveWallZ;

	// 動く壁の速度定数
	const float MoveWallSpeed;

	//X・Y軸のオブジェクトの間隔。
	const float Offset;
	// Z軸のオブジェクトの間隔
	const float OffsetZ;

	// プレイヤーの生成されるときのZ軸のポジション定数
	const float PlayerPositionZ;

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

	// 
	const Vector3 LightObjectSize;

	// リスポーンポイントオブジェクトの当たり判定サイズ（AABB）定数
	const AABB RespawnBox;

	// リスポーンポイントオブジェクトの当たり判定サイズ（AABB）定数
	const AABB LightPointBox;

	// スイッチのポジションは他のオブジェクトと違いずらす必要があるので
	// そのために用いる定数
	const float ShiftSwitchPositionZ;

	// レイヤー数の最大値
	const int MaxLayer;

	// レイヤーごとに割り当てるオブジェクトのZ軸の値を格納する配列
	float objectPositionZ[18];

public:

	CollectionObject* FindCollectionObject(CollectionTag _CollectionTag);

};

