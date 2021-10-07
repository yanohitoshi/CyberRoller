#pragma once
#include "StageCreatorBase.h"


class ResultSceneCreator :
    public StageCreatorBase
{
public:

	/*
	@fn コンストラクタ
	@brief  objectの生成を行う
	@param	_reUseGameObject 再利用するかどうかフラグ
	@param	_objectTag オブジェクト判別用Tag
	*/
	ResultSceneCreator(bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief マップデータの削除を行う
	*/
	~ResultSceneCreator()override;

	/*
	@fn ファイルを開く
	@return 成功か否か
	*/
	bool OpenFile();

	/*
	@fn ステージを生成する
	*/
	void CreateStage();

private:

	/*
	@fn baseLayerクリエイター
	@brief  レイヤー1のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateResultMap(int _indexX, int _indexZ);

	/*
	@fn CameraTargetクリエイター
	@brief  レイヤー2のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	void CreateCamera(int _indexX, int _indexY);

	//タイトル表示用
	std::vector<std::vector<int>> resultMapData;
	std::vector<std::vector<int>> resultCameraData;

	// マップデータの配列サイズX
	int sizeX;
	// マップデータの配列サイズY
	int sizeY;

	// タイトルでのプレイヤー生成ナンバー
	const int SwitchNumber;
	// タイトルでのグラウンドオブジェクト生成ナンバー
	const int CameraNumber;

	// リザルトシーンでのObject間の間隔
	const float ResultOffset;

};

