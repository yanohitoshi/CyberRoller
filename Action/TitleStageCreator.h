#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file TitleStageCreator.h
@brief TitleStageを生成する
*/
class TitleStageCreator :
    public StageCreatorBase
{
public:

	/*
	@fn コンストラクタ
	@brief  objectの生成を行う
	@param	_reUseGameObject 再利用するかどうかフラグ
	@param	_objectTag オブジェクト判別用Tag
	*/
	TitleStageCreator(bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~TitleStageCreator()override;

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
	@fn レイヤー1クリエイター
	@brief  レイヤー1のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	@param	_playerPos タイトルプレイヤーオブジェクトのポジション
	*/
	void CreateTitleMap(int _indexX, int _indexY, Vector3 _playerPos);

	/*
	@fn レイヤー2クリエイター
	@brief  レイヤー2のマップデータに含まれるオブジェクトの生成を行う
	@param	_indexX 検索するマップデータの添え字X
	@param	_indexY 検索するマップデータの添え字Y
	*/
	Vector3 CreatePlayer(int _indexX, int _indexY);

	//タイトル表示用
	std::vector<std::vector<int>> titleMapData;
	std::vector<std::vector<int>> titlePlayerData;

	// マップデータの配列サイズX
	int sizeX;
	// マップデータの配列サイズY
	int sizeY;

	// タイトルでのプレイヤー生成ナンバー
	const int PlayerNumber;
	// タイトルでのグラウンドオブジェクト生成ナンバー
	const int GroundNumber;

	// 配置するオブジェクトの間隔
	const float Offset;

	// ブロックサイズ定数
	const Vector3 BlockSize;

	// タイトルのプレイヤーのポジション用変数
	Vector3 playerPos;

};

