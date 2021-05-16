#include "FirstStageCreator.h"
#include "BoxObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "NextSceneObject.h"
#include "NeedlePanelObject.h"
#include "RespawnPoint.h"
#include "PushBoxObject.h"
#include "SwitchBaseObject.h"

/*
   @fn コンストラクタ
   @brief block同士の間隔の初期化(offset)
 */

FirstStageCreator::FirstStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
{
}

/*
  @fn デストラクタ
 */

FirstStageCreator::~FirstStageCreator()
{
	//マップデータの後始末
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	playerData.clear();

}

bool FirstStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/firstStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// ステージデータ読み込み (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/firstStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}

	// ステージデータ読み込み (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/firstStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}

	// ステージデータ読み込み (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/firstStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}

	// ステージデータ読み込み (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/firstStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (player) 
	if (!readTiledJson(playerData, "Assets/Config/firstStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	return false;
}

PlayerObject* FirstStageCreator::CreatePlayer()
{
	//playerクラスに初期位置を渡すための変数生成
	Vector3 pos = Vector3(0, 0, 0);

	// プレイヤーの位置情報検索
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// プレイヤーデータ内にプレイヤー生成情報があれば
			if (playerData[iy][ix] == 19)
			{
				// 配列の添え字とオブジェクトごとの間隔を用いてポジションを設定
				pos = Vector3(Offset * ix, -Offset * iy, 500);
			}
		}
	}

	// プレイヤーオブジェクト生成
	playerObject = new PlayerObject(pos, false, Tag::PLAYER);

	// メインカメラ生成と同時にプレイヤーオブジェクトのポインタを渡す
	GameObject::CreateMainCamera(pos, playerObject);

	// プレイヤーオブジェクトのポインタを返す
	return playerObject;
}

void FirstStageCreator::CreateStage()
{
	// ステージデータを見てその情報ごとのclassを生成する
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// Layer1内を検索
			CreateLayer1(ix, iy);
			// Layer2内を検索
			CreateLayer2(ix, iy);
			// Layer3内を検索
			CreateLayer3(ix, iy);
			// Layer4内を検索
			CreateLayer4(ix, iy);
			// Layer5内を検索
			CreateLayer5(ix, iy);
		}
	}
}

void FirstStageCreator::CreateLayer1(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer1 = layer1StageData[_indexY][_indexX];
	// レイヤー1のマップオブジェクトのポジション
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, 0.0f);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer1)
	{
	case(LAYER1_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer1Pos, BlockSize, Tag::GROUND);
		break;
	}

}

void FirstStageCreator::CreateLayer2(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer2 = layer2StageData[_indexY][_indexX];
	// レイヤー2のマップオブジェクトのポジション
	Vector3 layer2Pos = Vector3(Offset * _indexX, -Offset * _indexY, 200.0f);
	// レイヤー2のスイッチ系マップオブジェクトのポジション
	Vector3 layer2SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 100.0f);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer2)
	{
	case(LAYER2_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer2Pos, BlockSize, Tag::GROUND);
		break;
	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer2SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer2SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}

}

void FirstStageCreator::CreateLayer3(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer3 = layer3StageData[_indexY][_indexX];
	// レイヤー3のマップオブジェクトのポジション
	Vector3 layer3Pos = Vector3(Offset * _indexX, -Offset * _indexY, 400.0f);
	// レイヤー3のスイッチ系マップオブジェクトのポジション
	Vector3 layer3SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 300.0f);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer3)
	{
	case(LAYER3_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer3Pos, BlockSize, Tag::GROUND);
		break;
	case(PORTRAIT_WALL_PARTS):
		// 縦長壁オブジェクトの生成
		new WallBlockObject(layer3Pos, PortraitWallBlockSize, Tag::WALL);
		break;
	case(LANDSCAPE_WALL_PARTS):
		// 横長壁オブジェクトの生成
		new WallBlockObject(layer3Pos, LandscapeWallBlockSize, Tag::WALL);
		break;
	}

}

void FirstStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer4 = layer4StageData[_indexY][_indexX];
	// レイヤー4のマップオブジェクトのポジション
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, 600.0f);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer4Pos, BlockSize, Tag::GROUND);
		break;
	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer4Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	}

}

void FirstStageCreator::CreateLayer5(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer5 = layer5StageData[_indexY][_indexX];
	// レイヤー5のマップオブジェクトのポジション
	Vector3 layer5Pos = Vector3(Offset * _indexX, -Offset * _indexY, 800.0f);
	// レイヤー5のスイッチ系マップオブジェクトのポジション
	Vector3 layer5SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 700.0f);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer5)
	{
	case(LAYER5_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer5Pos, BlockSize, Tag::GROUND);
		break;
	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::TUTORIAL_SWITCH);
		break;
	case(CLEAR_OBJECT_PARTS):
		// ステージクリアオブジェクト生成
		new NextSceneObject(Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z), Tag::TUTORIAL_CLEAR_POINT, playerObject);
		break;
	case(FIRST_MOVE_WALL_PARTS):
		// 第一区画の動く壁オブジェクト生成
		new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + ShiftMoveWallY, layer5Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::TUTORIAL_MOVE_WALL, MoveWallSpeed,
			Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - SmallMoveWallSize.z));
		break;
	}
}
