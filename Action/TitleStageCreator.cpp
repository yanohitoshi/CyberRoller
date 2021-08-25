//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitleStageCreator.h"
#include "BoxObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "ClearPointObject.h"
#include "TitlePlayerObject.h"
#include "TitleGroundObject.h"


/*
   @fn コンストラクタ
   @brief block同士の間隔の初期化(offset)
 */
TitleStageCreator::TitleStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, PlayerNumber(3)
	, GroundNumber(79)
	, playerPos(Vector3::Zero)
	, TitlePlayerPositionZ(100.0f)
	, TitleBlockPositionZ(0.0f)
{
}

/*
  @fn デストラクタ
 */
TitleStageCreator::~TitleStageCreator()
{
	//マップデータの削除
	titleMapData.clear();
	titlePlayerData.clear();
}

bool TitleStageCreator::OpenFile()
{

	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(titleMapData, "Assets/Config/TitleMap.json", "baselayer"))
	{
		printf("do'nt have Layer/Titlebaselayer\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = titleMapData[0].size();
	sizeY = titleMapData.size();

	// ステージデータ読み込み (player)
	if (!readTiledJson(titlePlayerData, "Assets/Config/TitleMap.json", "player"))
	{
		printf("do'nt have Layer/Titleplayer\n");
		return true;
	}

	return false;
}

void TitleStageCreator::CreateStage()
{
	// 他クラスにプレイヤーのポジションを送るための変数
	Vector3 sendPlayerPos = Vector3::Zero;

	// プレイヤーのステージデータを見てその情報ごとのclassを生成する
	// 先にプレイヤーのポジションを確定させてその後そのポジションを他クラスに送りたいので
	// プレイヤーの位置データを回し切っています
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// プレイヤー生成関数
			sendPlayerPos = CreatePlayer(ix,iy);
		}
	}

	// ステージデータを見てその情報ごとのclassを生成する
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// タイトル用マップステージ生成関数
			CreateTitleMap(ix, iy, sendPlayerPos);
		}
	}

	// タイトル用カメラ生成
	GameObject::CreateTitleCamera(sendPlayerPos);

}

void TitleStageCreator::CreateTitleMap(int _indexX, int _indexY,Vector3 _playerPos)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int baseLayer = titleMapData[(int)_indexY][(int)_indexX];
	// タイトルステージのマップオブジェクトのポジション
	Vector3 baseLayerPos = Vector3(Offset * _indexX, -Offset * _indexY, TitleBlockPositionZ);

	// マップデータが生成ナンバーだったら
	if (baseLayer == GroundNumber)
	{
		// タイトル用オブジェクトの生成
		new TitleGroundObject(baseLayerPos, BlockSize, _playerPos,Tag::TITLE_OBJECT);
	}
}

Vector3 TitleStageCreator::CreatePlayer(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int playerLayer = titlePlayerData[(int)_indexY][(int)_indexX];
	// タイトルでのプレイヤーオブジェクトのポジション
	Vector3 objectPos = Vector3(Offset * _indexX, -Offset * _indexY, TitlePlayerPositionZ);
	
	// マップデータが生成ナンバーだったら
	if (playerLayer == PlayerNumber)
	{
		// タイトル用プレイヤーの生成
		new TitlePlayerObject(objectPos, false, Tag::TITLE_PLAYER);
		// ポジションを保存
		playerPos = objectPos;
	}

	// プレイヤーのポジションを返す
	return playerPos;

}
