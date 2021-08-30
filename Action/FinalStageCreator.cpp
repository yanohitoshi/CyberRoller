//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FinalStageCreator.h"
#include "BoxObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "NextSceneObject.h"
#include "ClearPointObject.h"
#include "RespawnPoint.h"
#include "NeedlePanelObject.h"
#include "MoveBlockObject.h"
#include "PushBoxObject.h"
#include "SwitchBaseObject.h"

/*
   @fn コンストラクタ
   @brief block同士の間隔の初期化(Offset)
*/
FinalStageCreator::FinalStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(17)
	, LightPointPositionZ(7000.0f)
{
}

/*
  @fn デストラクタ
*/
FinalStageCreator::~FinalStageCreator()
{
	//マップデータの削除
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	layer6StageData.clear();
	layer7StageData.clear();
	layer8StageData.clear();
	layer9StageData.clear();
	layer10StageData.clear();
	layer11StageData.clear();
	layer12StageData.clear();
	layer13StageData.clear();
	layer14StageData.clear();
	layer15StageData.clear();
	layer16StageData.clear();
	layer17StageData.clear();

	//プレイヤーのマップデータ削除
	playerData.clear();

}

bool FinalStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/finalStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// ステージデータ読み込み (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/finalStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// ステージデータ読み込み (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/finalStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// ステージデータ読み込み (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/finalStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// ステージデータ読み込み (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/finalStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/finalStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}
	// ステージデータ読み込み (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/finalStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}
	// ステージデータ読み込み (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/finalStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}
	// ステージデータ読み込み (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/finalStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer9\n");
		return true;
	}
	// ステージデータ読み込み (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/finalStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}
	// ステージデータ読み込み (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/finalStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}
	// ステージデータ読み込み (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/finalStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}
	// ステージデータ読み込み (layer13) 
	if (!readTiledJson(layer13StageData, "Assets/Config/finalStageMap.json", "layer13"))
	{
		printf("do'nt have Layer/layer13\n");
		return true;
	}
	// ステージデータ読み込み (layer14) 
	if (!readTiledJson(layer14StageData, "Assets/Config/finalStageMap.json", "layer14"))
	{
		printf("do'nt have Layer/layer14\n");
		return true;
	}
	// ステージデータ読み込み (layer15) 
	if (!readTiledJson(layer15StageData, "Assets/Config/finalStageMap.json", "layer15"))
	{
		printf("do'nt have Layer/layer15\n");
		return true;
	}
	// ステージデータ読み込み (layer16) 
	if (!readTiledJson(layer16StageData, "Assets/Config/finalStageMap.json", "layer16"))
	{
		printf("do'nt have Layer/layer16\n");
		return true;
	}
	// ステージデータ読み込み (layer17) 
	if (!readTiledJson(layer17StageData, "Assets/Config/finalStageMap.json", "layer17"))
	{
		printf("do'nt have Layer/layer17\n");
		return true;
	}

	// ステージデータ読み込み (player) 
	if (!readTiledJson(playerData, "Assets/Config/finalStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}


	return false;
}

void FinalStageCreator::CreateStage()
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
			// Layer6内を検索
			CreateLayer6(ix, iy);
			// Layer7内を検索
			CreateLayer7(ix, iy);
			// Layer8内を検索
			CreateLayer8(ix, iy);
			// Layer9内を検索
			CreateLayer9(ix, iy);
			// Layer10内を検索
			CreateLayer10(ix, iy);
			// Layer11内を検索
			CreateLayer11(ix, iy);
			// Layer12内を検索
			CreateLayer12(ix, iy);
			// Layer13内を検索
			CreateLayer13(ix, iy);
			// Layer14内を検索
			CreateLayer14(ix, iy);
			// Layer15内を検索
			CreateLayer15(ix, iy);
			// Layer16内を検索
			CreateLayer16(ix, iy);
			// Layer17内を検索
			CreateLayer17(ix, iy);
		}
	}
}

PlayerObject* FinalStageCreator::CreatePlayer()
{

	// プレイヤーの位置情報検索
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// プレイヤーを生成する処理
			ProductionPlayer(playerData[iy][ix], ix, iy);
		}
	}

	// プレイヤーオブジェクトのポインタを返す
	return playerObject;

}

void FinalStageCreator::CreateLayer1(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer1 = layer1StageData[_indexY][_indexX];
	// レイヤー1のマップオブジェクトのポジション
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer1)
	{
	case(LAYER1_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer1Pos, BlockSize, Tag::GROUND);
		break;
	}
}

void FinalStageCreator::CreateLayer2(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer2 = layer2StageData[_indexY][_indexX];
	// レイヤー2のマップオブジェクトのポジション
	Vector3 layer2Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1]);
	// レイヤー2のスイッチ系マップオブジェクトのポジション
	Vector3 layer2SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1] - ShiftSwitchPositionZ);

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

void FinalStageCreator::CreateLayer3(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer3 = layer3StageData[_indexY][_indexX];
	// レイヤー3のマップオブジェクトのポジション
	Vector3 layer3Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2]);
	// レイヤー3のスイッチ系マップオブジェクトのポジション
	Vector3 layer3SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer3)
	{
	case(LAYER3_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer3Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer3SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

void FinalStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer4 = layer4StageData[_indexY][_indexX];
	// レイヤー4のマップオブジェクトのポジション
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3]);
	// レイヤー4のスイッチ系マップオブジェクトのポジション
	Vector3 layer4SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer4Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer4SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(LEFT_MOVE_GROUND_NUMBER_1):
		new MoveBlockObject(layer4Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, -1600.0f, 0.0f), Vector3::NegUnitY, 400.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer5(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer5 = layer5StageData[_indexY][_indexX];
	// レイヤー5のマップオブジェクトのポジション
	Vector3 layer5Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4]);
	// レイヤー5のスイッチ系マップオブジェクトのポジション
	Vector3 layer5SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer5)
	{
	case(LAYER5_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer5Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer5SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer5SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// 第一区画の動く壁オブジェクト生成
		new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + ShiftMoveWallY, layer5Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - BigMoveWallSize.z));
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer5Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(LEFT_PUSH_BOX_NUMBER_1):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(LEFT_PUSH_BOX_NUMBER_2):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1450.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(LEFT_PUSH_BOX_NUMBER_3):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1400.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(LEFT_PUSH_BOX_NUMBER_4):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1300.0f, 0.2f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_1):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_2):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1450.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_3):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1400.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_4):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1300.0f, 0.2f, MoveDirectionTag::MOVE_Y);
		break;

	case(FRONT_MOVE_GROUND_NUMBER_1):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(1400.0f, 0.0f, 0.0f), Vector3::UnitX, 400.0f, MoveDirectionTag::MOVE_X);
		break;

	case(BACK_MOVE_GROUND_NUMBER_1):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(-1600.0f, 0.0f, 0.0f), Vector3::NegUnitX, 400.0f, MoveDirectionTag::MOVE_X);
		break;

	case(FRONT_MOVE_GROUND_NUMBER_3):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(1600.0f, 0.0f, 0.0f), Vector3::UnitX, 800.0f, MoveDirectionTag::MOVE_X);
		break;

	case(BACK_MOVE_GROUND_NUMBER_2):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(-1600.0f, 0.0f, 0.0f), Vector3::NegUnitX, 800.0f, MoveDirectionTag::MOVE_X);
		break;

	case(LEFT_MOVE_GROUND_NUMBER_2):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, -1400.0f, 0.0f), Vector3::NegUnitY, 700.0f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_MOVE_GROUND_NUMBER_1):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, 1400.0f, 0.0f), Vector3::UnitY, 700.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer6(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer6 = layer6StageData[_indexY][_indexX];
	// レイヤー6のマップオブジェクトのポジション
	Vector3 layer6Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5]);
	// レイヤー6のスイッチ系マップオブジェクトのポジション
	Vector3 layer6SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer6)
	{
	case(LAYER6_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer6Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer6SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer6SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(LEFT_PUSH_BOX_NUMBER_5):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer6Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1200.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;
		
	case(RIGHT_PUSH_BOX_NUMBER_5):
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer6Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1800.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer7(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer7 = layer7StageData[_indexY][_indexX];
	// レイヤー7のマップオブジェクトのポジション
	Vector3 layer7Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6]);
	// レイヤー7のスイッチ系マップオブジェクトのポジション
	Vector3 layer7SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer7)
	{
	case(LAYER7_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer7Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer7SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(LEFT_MOVE_GROUND_NUMBER_3):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer7Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, -800.0f, 0.0f), Vector3::NegUnitY, 400.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer8(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer8 = layer8StageData[_indexY][_indexX];
	// レイヤー8のマップオブジェクトのポジション
	Vector3 layer8Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7]);
	// レイヤー8のスイッチ系マップオブジェクトのポジション
	Vector3 layer8SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer8)
	{
	case(LAYER8_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer8Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer8SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer8SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer8SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(RIGHT_MOVE_GROUND_NUMBER_2):
		// ケースごとに方向の違う動く床を生成
		new MoveBlockObject(layer8Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, 800.0f, 0.0f), Vector3::UnitY, 400.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer9(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer9 = layer9StageData[_indexY][_indexX];
	// レイヤー9のマップオブジェクトのポジション
	Vector3 layer9Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8]);
	// レイヤー9のスイッチ系マップオブジェクトのポジション
	Vector3 layer9SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer9)
	{
	case(LAYER9_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer9Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer9SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer9SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

void FinalStageCreator::CreateLayer10(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer10 = layer10StageData[_indexY][_indexX];
	// レイヤー10のマップオブジェクトのポジション
	Vector3 layer10Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9]);
	// レイヤー10のスイッチ系マップオブジェクトのポジション
	Vector3 layer10SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer10)
	{
	case(LAYER10_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer10Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer10SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// 第二区画の動く壁オブジェクト生成
		new MoveWallBlock(Vector3(layer10Pos.x, layer10Pos.y + ShiftMoveWallY, layer10Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::SECOND_MOVE_WALL, MoveWallSpeed,
			Vector3(layer10Pos.x, layer10Pos.y, layer10Pos.z - BigMoveWallSize.z));
		break;
	}
}

void FinalStageCreator::CreateLayer11(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer11 = layer11StageData[_indexY][_indexX];
	// レイヤー11のマップオブジェクトのポジション
	Vector3 layer11Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10]);
	// レイヤー11のスイッチ系マップオブジェクトのポジション
	Vector3 layer11SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer11)
	{
	case(LAYER11_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer11Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer11SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer11SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer11SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

void FinalStageCreator::CreateLayer12(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer12 = layer12StageData[_indexY][_indexX];
	// レイヤー12のマップオブジェクトのポジション
	Vector3 layer12Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11]);
	// レイヤー12のスイッチ系マップオブジェクトのポジション
	Vector3 layer12SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer12)
	{
	case(LAYER12_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer12Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer12SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer12SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

void FinalStageCreator::CreateLayer13(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer13 = layer13StageData[_indexY][_indexX];
	// レイヤー13のマップオブジェクトのポジション
	Vector3 layer13Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12]);
	// レイヤー13のスイッチ系マップオブジェクトのポジション
	Vector3 layer13SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer13)
	{
	case(LAYER13_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer13Pos, BlockSize, Tag::GROUND);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer13SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer13SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

void FinalStageCreator::CreateLayer14(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer14 = layer14StageData[_indexY][_indexX];
	// レイヤー14のマップオブジェクトのポジション
	Vector3 layer14Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13]);
	// レイヤー14のスイッチ系マップオブジェクトのポジション
	Vector3 layer14SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer14)
	{
	case(LAYER14_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer14Pos, BlockSize, Tag::GROUND);
		break;

	case(THIRD_SWITCH_PARTS):
		// 第三区画スイッチオブジェクト生成
		new SwitchBaseObject(layer14SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer14SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(THIRD_MOVE_WALL_PARTS):
		// 第三区画の動く壁オブジェクト生成
		new MoveWallBlock(Vector3(layer14Pos.x, layer14Pos.y + ShiftMoveWallY, layer14Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer14Pos.x, layer14Pos.y, layer14Pos.z - BigMoveWallSize.z));
		break;
	}
}

void FinalStageCreator::CreateLayer15(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer15 = layer15StageData[_indexY][_indexX];
	// レイヤー8のマップオブジェクトのポジション
	Vector3 layer15Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[14]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer15)
	{
	case(LAYER15_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer15Pos, BlockSize, Tag::GROUND);
		break;
	}
}

void FinalStageCreator::CreateLayer16(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer16 = layer16StageData[_indexY][_indexX];
	// レイヤー16のマップオブジェクトのポジション
	Vector3 layer16Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[15]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer16)
	{
	case(LAYER16_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer16Pos, BlockSize, Tag::GROUND);
		break;
	}
}

void FinalStageCreator::CreateLayer17(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int layer17 = layer17StageData[_indexY][_indexX];
	// レイヤー17のマップオブジェクトのポジション
	Vector3 layer17Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[16]);
	// レイヤー17のスイッチ系マップオブジェクトのポジション
	Vector3 layer17SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 3101.0f);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (layer17)
	{
	case(LAYER17_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new BoxObject(layer17Pos, BlockSize, Tag::GROUND);
		break;

	case(CLEAR_OBJECT_PARTS):
		// ステージクリアオブジェクト生成
		new ClearPointObject(Vector3(layer17Pos.x, layer17Pos.y, layer17Pos.z), Tag::CLEAR_POINT, playerObject);
		break;
	}
}

