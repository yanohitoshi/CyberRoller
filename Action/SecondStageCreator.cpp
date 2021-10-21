//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SecondStageCreator.h"
#include "GroundObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "NextSceneObject.h"
#include "RespawnPoint.h"
#include "NeedlePanelObject.h"
#include "MoveBlockObject.h"
#include "SwitchBaseObject.h"
#include "EnemyObjectBase.h"
#include "NormalEnemyObject.h"
#include "MoveEnemyObject.h"
#include "TrackingEnemyObject.h"
#include "LightObject.h"
#include "CameraChangePoint.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
@param	_reUseGameObject 再利用するかどうかフラグ
@param	_objectTag オブジェクト判別用Tag
*/
SecondStageCreator::SecondStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(12)
	, LightPointPositionZ(4800.0f)
{
}

/*
@fn デストラクタ
@brief マップデータの削除を行う
*/
SecondStageCreator::~SecondStageCreator()
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
	cameraDirectingData.clear();
	playerData.clear();
}

/*
@fn ファイルを開く
@return 成功か否か
*/
bool SecondStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/secondStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// ステージデータ読み込み (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/secondStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}

	// ステージデータ読み込み (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/secondStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}

	// ステージデータ読み込み (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/secondStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}

	// ステージデータ読み込み (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/secondStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/secondStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}

	// ステージデータ読み込み (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/secondStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}

	// ステージデータ読み込み (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/secondStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}

	// ステージデータ読み込み (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/secondStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/secondStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}

	// ステージデータ読み込み (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/secondStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}

	// ステージデータ読み込み (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/secondStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}

	// ステージデータ読み込み (player) 
	if (!readTiledJson(playerData, "Assets/Config/secondStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	// ステージデータ読み込み (CameraDirecting)
	if (!readTiledJson(cameraDirectingData, "Assets/Config/secondStageMap.json", "CameraDirecting"))
	{
		printf("do'nt have Layer/CameraDirecting\n");
		return true;
	}


	return false;

}

/*
@fn ステージを生成する
*/
void SecondStageCreator::CreateStage()
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
			CreateCameraDirecting(ix, iy);
		}
	}
}

/*
@fn プレイヤーを生成する
*/
PlayerObject* SecondStageCreator::CreatePlayer()
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

/*
@fn レイヤー1クリエイター
@brief  レイヤー1のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer1(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer1 = layer1StageData[_indexY][_indexX];
	// レイヤー1のマップオブジェクトのポジション
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer1)
	{
	case(LAYER1_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer1Pos, BlockSize, Tag::GROUND);
		break;
	}

}

/*
@fn レイヤー2クリエイター
@brief  レイヤー2のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer2(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer2 = layer2StageData[_indexY][_indexX];
	// レイヤー2のマップオブジェクトのポジション
	Vector3 layer2Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1]);
	// レイヤー2のスイッチ系マップオブジェクトのポジション
	Vector3 layer2SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer2)
	{
	case(LAYER2_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer2Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer2SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer2SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer2Pos, Tag::ENEMY, playerObject);
		break;
	}

}

/*
@fn レイヤー3クリエイター
@brief  レイヤー3のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer3(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer3 = layer3StageData[_indexY][_indexX];
	// レイヤー3のマップオブジェクトのポジション
	Vector3 layer3Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2]);
	// レイヤー3のスイッチ系マップオブジェクトのポジション
	Vector3 layer3SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer3)
	{
	case(LAYER3_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer3Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer3Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer3Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer3SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer3SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

/*
@fn レイヤー4クリエイター
@brief  レイヤー4のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer4 = layer4StageData[_indexY][_indexX];
	// レイヤー4のマップオブジェクトのポジション
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3]);
	// レイヤー4のスイッチ系マップオブジェクトのポジション
	Vector3 layer4SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3] - ShiftSwitchPositionZ);
	
	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer4Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer4Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer4Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer4SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_STAGE_RIGHT_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(0.0f, 1600.0f, 0.0f), Vector3::UnitY, 200.0f, MoveDirectionTag::MOVE_Y);
		// 動く床を生成
		new MoveBlockObject(layer4Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;
	}
}

/*
@fn レイヤー5クリエイター
@brief  レイヤー5のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer5(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer5 = layer5StageData[_indexY][_indexX];
	// レイヤー5のマップオブジェクトのポジション
	Vector3 layer5Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4]);
	// レイヤー5のスイッチ系マップオブジェクトのポジション
	Vector3 layer5SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer5)
	{
	case(LAYER5_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer5Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer5SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

/*
@fn レイヤー6クリエイター
@brief  レイヤー6のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer6(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer6 = layer6StageData[_indexY][_indexX];
	// レイヤー6のマップオブジェクトのポジション
	Vector3 layer6Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5]);
	// レイヤー6のスイッチ系マップオブジェクトのポジション
	Vector3 layer6SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer6)
	{
	case(LAYER6_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer6Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer6Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer6Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer6SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// 第一区画の動く壁オブジェクト生成
		new MoveWallBlock(Vector3(layer6Pos.x, layer6Pos.y + ShiftMoveWallY, layer6Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer6Pos.x, layer6Pos.y, layer6Pos.z - SmallMoveWallSize.z));
		break;

	case(SECOND_STAGE_RIGHT_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(0.0f, 800.0f, 0.0f), Vector3::UnitY, 200.0f, MoveDirectionTag::MOVE_Y);
		// 動く床を生成
		new MoveBlockObject(layer6Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(SECOND_STAGE_LEFT_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(0.0f, -800.0f, 0.0f), Vector3::NegUnitY, 350.0f, MoveDirectionTag::MOVE_Y);
		// 動く床を生成
		new MoveBlockObject(layer6Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer6Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;
	}
}

/*
@fn レイヤー7クリエイター
@brief  レイヤー7のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer7(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer7 = layer7StageData[_indexY][_indexX];
	// レイヤー7のマップオブジェクトのポジション
	Vector3 layer7Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6]);
	// レイヤー7のスイッチ系マップオブジェクトのポジション
	Vector3 layer7SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer7)
	{
	case(LAYER7_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer7Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer7Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer7Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer7SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer7SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer7Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 左右に動く敵固有のデータ構造体をセット
		SetMoveEnemyData(200.0f, Vector3::UnitY, 800.0f, MoveEnemyTag::RIGHT_MOVE);
		// 左右に動く敵の生成
		new MoveEnemyObject(layer7Pos, Tag::ENEMY, playerObject, moveEnemyData);
		break;

	case(LEFT_MOVE_ENEMY_PARTS):
		// 左右に動く敵固有のデータ構造体をセット
		SetMoveEnemyData(200.0f, Vector3::NegUnitY, 800.0f, MoveEnemyTag::LEFT_MOVE);
		// 左右に動く敵の生成
		new MoveEnemyObject(layer7Pos, Tag::ENEMY, playerObject, moveEnemyData);
		break;
	}
}

/*
@fn レイヤー8クリエイター
@brief  レイヤー8のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer8(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer8 = layer8StageData[_indexY][_indexX];
	// レイヤー8のマップオブジェクトのポジション
	Vector3 layer8Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7]);
	// レイヤー8のスイッチ系マップオブジェクトのポジション
	Vector3 layer8SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer8)
	{
	case(LAYER8_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer8Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer8Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer8Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer8SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer8SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// 第二区画の動く壁オブジェクト生成
		lastMoveWallBlock = new MoveWallBlock(Vector3(layer8Pos.x, layer8Pos.y + ShiftMoveWallY, layer8Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer8Pos.x, layer8Pos.y, layer8Pos.z - SmallMoveWallSize.z));
		break;

	case(TRACKING_ENEMY_PARTS):
		new TrackingEnemyObject(layer8Pos, Tag::ENEMY, 600.0f, playerObject, 1400.0f);
		break;
	}
}

/*
@fn レイヤー9クリエイター
@brief  レイヤー9のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer9(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer9 = layer9StageData[_indexY][_indexX];
	// レイヤー9のマップオブジェクトのポジション
	Vector3 layer9Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer9)
	{
	case(LAYER9_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer9Pos, BlockSize, Tag::GROUND);
		break;
	}
}

/*
@fn レイヤー10クリエイター
@brief  レイヤー10のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer10(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer10 = layer10StageData[_indexY][_indexX];
	// レイヤー10のマップオブジェクトのポジション
	Vector3 layer10Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer10)
	{
	case(LAYER10_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer10Pos, BlockSize, Tag::GROUND);
		break;
	}
}

/*
@fn レイヤー11クリエイター
@brief  レイヤー11のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer11(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer11 = layer11StageData[_indexY][_indexX];
	// レイヤー11のマップオブジェクトのポジション
	Vector3 layer11Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer11)
	{
	case(LAYER11_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer11Pos, BlockSize, Tag::GROUND);

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(CLEAR_OBJECT_PARTS):
		// ステージクリアオブジェクト生成
		new NextSceneObject(layer11Pos, Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;
	}
}

/*
@fn レイヤー12クリエイター
@brief  レイヤー12のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void SecondStageCreator::CreateLayer12(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer12 = layer12StageData[_indexY][_indexX];
	// レイヤー12のマップオブジェクトのポジション
	Vector3 layer12Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer12)
	{
	case(CLEAR_OBJECT_PARTS):
		// ステージクリアオブジェクト生成
		new NextSceneObject(Vector3(layer12Pos.x, layer12Pos.y, layer12Pos.z), Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;
	}
}

void SecondStageCreator::CreateCameraDirecting(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int CameraDirectingData = cameraDirectingData[_indexY][_indexX];
	// レイヤー1のマップオブジェクトのポジション
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (CameraDirectingData)
	{
	case(38):
		AABB aabb = { Vector3(-6000.0f,-1800.0f,0.0f),Vector3(3600.0f,1800.0f,4000.0f) };
		// ブロックオブジェクト生成
		new CameraChangePoint(layer1Pos, aabb, Tag::CAMERA_CHANGE_BEHIND);
		break;
	}
}
