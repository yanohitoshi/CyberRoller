#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"

/*
@file FinalStageCreator.h
@brief FinalStageを生成する
*/
class FinalStageCreator :
    public StageCreatorBase
{
public:

	/*
	@fn コンストラクタ
	@brief  objectの生成を行う
	@param	_reUseGameObject 再利用するかどうかフラグ
	@param	_objectTag オブジェクト判別用Tag
	*/
	FinalStageCreator(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~FinalStageCreator()override;
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

	// 押し出し板のナンバー列挙
	// 現在の仕様上こういった形でしか列挙出来ませんでした。
	// 改善案模索中です
	enum FinalStagePushBoxNumber
	{
		// 左向きの押し出し板の列挙ナンバー
		LEFT_PUSH_BOX_NUMBER_1 = 46,
		LEFT_PUSH_BOX_NUMBER_2 = 47,
		LEFT_PUSH_BOX_NUMBER_3 = 48,
		LEFT_PUSH_BOX_NUMBER_4 = 49,
		LEFT_PUSH_BOX_NUMBER_5 = 44,

		// 右向きの押し出し板の列挙ナンバー
		RIGHT_PUSH_BOX_NUMBER_1 = 50,
		RIGHT_PUSH_BOX_NUMBER_2 = 51,
		RIGHT_PUSH_BOX_NUMBER_3 = 52,
		RIGHT_PUSH_BOX_NUMBER_4 = 53,
		RIGHT_PUSH_BOX_NUMBER_5 = 45,

	};

	// 動く床のナンバー列挙
	// 現在の仕様上こういった形でしか列挙出来ませんでした。
	// 改善案模索中です
	enum FinalStageMoveGroundNumber
	{
		// 最初の移動方向が前移動の動く地面の列挙ナンバー
		FRONT_MOVE_GROUND_NUMBER_1 = 5,
		FRONT_MOVE_GROUND_NUMBER_3 = 9,

		// 最初の移動方向が後ろ移動の動く地面の列挙ナンバー
		BACK_MOVE_GROUND_NUMBER_1 = 6,
		BACK_MOVE_GROUND_NUMBER_2 = 10,

		// 最初の移動方向が左移動の動く地面の列挙ナンバー
		LEFT_MOVE_GROUND_NUMBER_1 = 11,
		LEFT_MOVE_GROUND_NUMBER_2 = 12,
		LEFT_MOVE_GROUND_NUMBER_3 = 7,

		// 最初の移動方向が右移動の動く地面の列挙ナンバー
		RIGHT_MOVE_GROUND_NUMBER_1 = 13,
		RIGHT_MOVE_GROUND_NUMBER_2 = 8,

	};

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
	/*
	@fn レイヤー6クリエイター
	@brief  レイヤー6のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer6(int _indexX, int _indexY);

	/*
	@fn レイヤー7クリエイター
	@brief  レイヤー7のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer7(int _indexX, int _indexY);

	/*
	@fn レイヤー8クリエイター
	@brief  レイヤー8のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer8(int _indexX, int _indexY);

	/*
	@fn レイヤー9クリエイター
	@brief  レイヤー9のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer9(int _indexX, int _indexY);

	/*
	@fn レイヤー10クリエイター
	@brief  レイヤー10のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer10(int _indexX, int _indexY);

	/*
	@fn レイヤー11クリエイター
	@brief  レイヤー11のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer11(int _indexX, int _indexY);

	/*
	@fn レイヤー12クリエイター
	@brief  レイヤー12のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer12(int _indexX, int _indexY);

	/*
	@fn レイヤー13クリエイター
	@brief  レイヤー13のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer13(int _indexX, int _indexY);

	/*
	@fn レイヤー14クリエイター
	@brief  レイヤー14のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer14(int _indexX, int _indexY);

	/*
	@fn レイヤー15クリエイター
	@brief  レイヤー15のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer15(int _indexX, int _indexY);

	/*
	@fn レイヤー16クリエイター
	@brief  レイヤー16のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer16(int _indexX, int _indexY);

	/*
	@fn レイヤー17クリエイター
	@brief  レイヤー17のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLayer17(int _indexX, int _indexY);

	/*
	@fn ライトポイントクリエイター
	@brief  ライトポイントのマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateLightPoint(int _indexX, int _indexY);

	// 最終ステージのレイヤーの最大定数
	const int MaxLayerNumber;

	// ライトのZ軸ポジション
	const float LightPointPositionZ;
	
	// 最終ステージデータ
	std::vector<std::vector<int>> layer1StageData;
	std::vector<std::vector<int>> layer2StageData;
	std::vector<std::vector<int>> layer3StageData;
	std::vector<std::vector<int>> layer4StageData;
	std::vector<std::vector<int>> layer5StageData;
	std::vector<std::vector<int>> layer6StageData;
	std::vector<std::vector<int>> layer7StageData;
	std::vector<std::vector<int>> layer8StageData;
	std::vector<std::vector<int>> layer9StageData;
	std::vector<std::vector<int>> layer10StageData;
	std::vector<std::vector<int>> layer11StageData;
	std::vector<std::vector<int>> layer12StageData;
	std::vector<std::vector<int>> layer13StageData;
	std::vector<std::vector<int>> layer14StageData;
	std::vector<std::vector<int>> layer15StageData;
	std::vector<std::vector<int>> layer16StageData;
	std::vector<std::vector<int>> layer17StageData;

	std::vector<std::vector<int>> lightPointData;
	//playerのデータ
	std::vector<std::vector<int>> playerData;

	//配置するオブジェクトの間隔X
	int sizeX;
	//配置するオブジェクトの間隔Y
	int sizeY;
	
};

