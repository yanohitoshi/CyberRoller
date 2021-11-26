#pragma once
#include "StageCreatorBase.h"

/*
@file ForthStageCreator.h
@brief ForthStageを生成する
*/
class ForthStageCreator :
    public StageCreatorBase
{
public:

	/*
	@fn コンストラクタ
	@brief  objectの生成を行う
	@param	_reUseGameObject 再利用するかどうかフラグ
	@param	_objectTag オブジェクト判別用Tag
	*/
	ForthStageCreator(bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  マップデータの削除を行う
	*/
	~ForthStageCreator()override;

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

	// 最終ステージのレイヤーの最大定数
	const int MaxLayerNumber;

	// ライトのZ軸ポジション
	const float LightPointPositionZ;

	// 第4ステージデータ
	std::vector<std::vector<int>> cameraDirectingData;
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

	//playerのデータ
	std::vector<std::vector<int>> playerData;

	//配置するオブジェクトの間隔X
	int sizeX;
	//配置するオブジェクトの間隔Y
	int sizeY;
};

