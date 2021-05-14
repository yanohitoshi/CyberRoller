#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file FirstStageCreator.h
@brief FirstStageを生成する
*/
class FirstStageCreator 
	 : public StageCreatorBase
{
public:

	/*
	@fn コンストラクタ
	@brief  objectの生成を行う
	@param	_reUseGameObject 再利用するかどうかフラグ
	@param	_objectTag オブジェクト判別用Tag
	*/
	FirstStageCreator(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~FirstStageCreator()override;
	/*
	@fn ファイルを開く
	@return 成功か否か
	*/
	bool OpenFile();

	/*
	@fn プレイヤーを生成する
	*/
	class PlayerObject* CreatePlayer();

	/*
	@fn ステージを生成する
	*/
	void CreateStage();

private:

	/*
	@fn レイヤー1クリエイター
	@brief  レイヤー1のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer1(int _indexX, int _indexY);

	/*
	@fn レイヤー2クリエイター
	@brief  レイヤー2のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer2(int _indexX, int _indexY);

	/*
	@fn レイヤー3クリエイター
	@brief  レイヤー3のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer3(int _indexX, int _indexY);
	
	/*
	@fn レイヤー4クリエイター
	@brief  レイヤー4のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer4(int _indexX, int _indexY);

	/*
	@fn レイヤー5クリエイター
	@brief  レイヤー5のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer5(int _indexX, int _indexY);

	//ファーストステージデータ
	std::vector<std::vector<int>> layer1StageData;
	std::vector<std::vector<int>> layer2StageData;
	std::vector<std::vector<int>> layer3StageData;
	std::vector<std::vector<int>> layer4StageData;
	std::vector<std::vector<int>> layer5StageData;

	//playerのデータ
	std::vector<std::vector<int>> playerData;

	// マップデータの配列サイズX
	int sizeX;

	// マップデータの配列サイズY
	int sizeY;

	//配置するオブジェクトの間隔。サイズ
	const float Offset;

	// 動く壁のポジションを少しずらす定数
	// Y軸は中心のずらすため・Z軸は少し埋まった状態で生成したいため
	const float ShiftMoveWallY;
	const float ShiftMoveWallZ;

	// 動く壁の速度定数
	const float MoveWallSpeed;

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
	// 動く壁オブジェクトのサイズ定数
	const Vector3 MoveWallSize;

	// リスポーンポイントオブジェクトの当たり判定サイズ（AABB）定数
	const AABB RespawnBox;

};

