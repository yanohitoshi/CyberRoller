//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ThirdStageCreator.h"
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
#include "PushBoxObject.h"
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
ThirdStageCreator::ThirdStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(15)
	, LightPointPositionZ(7000.0f)
{
}

/*
@fn デストラクタ
@brief マップデータの削除を行う
*/
ThirdStageCreator::~ThirdStageCreator()
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
	cameraDirectingData.clear();
	// プレイヤーのマップデータ削除
	playerData.clear();
}

/*
@fn ファイルを開く
@return 成功か否か
*/
bool ThirdStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/thirdStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// ステージデータ読み込み (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/thirdStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// ステージデータ読み込み (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/thirdStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// ステージデータ読み込み (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/thirdStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// ステージデータ読み込み (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/thirdStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/thirdStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}
	// ステージデータ読み込み (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/thirdStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}
	// ステージデータ読み込み (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/thirdStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}
	// ステージデータ読み込み (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/thirdStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer9\n");
		return true;
	}
	// ステージデータ読み込み (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/thirdStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}
	// ステージデータ読み込み (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/thirdStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}
	// ステージデータ読み込み (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/thirdStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}
	// ステージデータ読み込み (layer13) 
	if (!readTiledJson(layer13StageData, "Assets/Config/thirdStageMap.json", "layer13"))
	{
		printf("do'nt have Layer/layer13\n");
		return true;
	}
	// ステージデータ読み込み (layer14) 
	if (!readTiledJson(layer14StageData, "Assets/Config/thirdStageMap.json", "layer14"))
	{
		printf("do'nt have Layer/layer14\n");
		return true;
	}
	// ステージデータ読み込み (layer15) 
	if (!readTiledJson(layer15StageData, "Assets/Config/thirdStageMap.json", "layer15"))
	{
		printf("do'nt have Layer/layer15\n");
		return true;
	}

	// ステージデータ読み込み (player) 
	if (!readTiledJson(playerData, "Assets/Config/thirdStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	// ステージデータ読み込み (CameraDirecting)
	if (!readTiledJson(cameraDirectingData, "Assets/Config/thirdStageMap.json", "CameraDirecting"))
	{
		printf("do'nt have Layer/CameraDirecting\n");
		return true;
	}

	return false;
}

/*
@fn ステージを生成する
*/
void ThirdStageCreator::CreateStage()
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
			CreateCameraDirecting(ix, iy);
		}
	}
}

/*
@fn プレイヤーを生成する
*/
PlayerObject* ThirdStageCreator::CreatePlayer()
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
void ThirdStageCreator::CreateLayer1(int _indexX, int _indexY)
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
void ThirdStageCreator::CreateLayer2(int _indexX, int _indexY)
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

	}

}

/*
@fn レイヤー3クリエイター
@brief  レイヤー3のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer3(int _indexX, int _indexY)
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

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer3SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer3SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer3SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer3SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn レイヤー4クリエイター
@brief  レイヤー4のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer4(int _indexX, int _indexY)
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

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer4SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn レイヤー5クリエイター
@brief  レイヤー5のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer5(int _indexX, int _indexY)
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

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer5SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_FRONT_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(1200.0f, 0.0f, 0.0f), Vector3::UnitX, 300.0f, MoveDirectionTag::MOVE_X);
		// 動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(THIRD_STAGE_BACK_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(-800.0f, 0.0f, 0.0f), Vector3::NegUnitX, 300.0f, MoveDirectionTag::MOVE_X);
		// 動く床を生成
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer5Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;
	}
}

/*
@fn レイヤー6クリエイター
@brief  レイヤー6のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer6(int _indexX, int _indexY)
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

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer6SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer6SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_LEFT_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(0.0f, -1400.0f, 0.0f), Vector3::NegUnitY, 300.0f, MoveDirectionTag::MOVE_Y);
		// 移動する床を生成
		new MoveBlockObject(layer6Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(TRACKING_ENEMY_PARTS):
		new TrackingEnemyObject(layer6Pos, Tag::ENEMY, 600.0f, playerObject, 1200.0f);
		break;

	case(RIGHT_PUSH_BOX):
		// プッシュボード固有のデータ構造体をセット
		SetPushBoxData(Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer6Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;
	}
}

/*
@fn レイヤー7クリエイター
@brief  レイヤー7のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer7(int _indexX, int _indexY)
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

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer7SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer7SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_RIGHT_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(0.0f, 1400.0f, 0.0f), Vector3::UnitY, 300.0f, MoveDirectionTag::MOVE_Y);
		// 動く床の生成
		new MoveBlockObject(layer7Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer7Pos, Tag::ENEMY, playerObject);
		break;
	}
}

/*
@fn レイヤー8クリエイター
@brief  レイヤー8のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer8(int _indexX, int _indexY)
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

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer8SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer8SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer8SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn レイヤー9クリエイター
@brief  レイヤー9のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer9(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer9 = layer9StageData[_indexY][_indexX];
	// レイヤー9のマップオブジェクトのポジション
	Vector3 layer9Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8]);
	// レイヤー9のスイッチ系マップオブジェクトのポジション
	Vector3 layer9SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer9)
	{
	case(LAYER9_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer9Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer9Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer9Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer9SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// 第一区画の動く壁オブジェクト生成
		new MoveWallBlock(Vector3(layer9Pos.x, layer9Pos.y + ShiftMoveWallY, layer9Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer9Pos.x, layer9Pos.y, layer9Pos.z - BigMoveWallSize.z));
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer9Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer9SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(TRACKING_ENEMY_PARTS):
		// 追跡する敵の生成
		new TrackingEnemyObject(layer9Pos, Tag::ENEMY, 600.0f, playerObject,1400.0f);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer9Pos, Tag::ENEMY, playerObject);
		break;
	}
}

/*
@fn レイヤー10クリエイター
@brief  レイヤー10のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer10(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer10 = layer10StageData[_indexY][_indexX];
	// レイヤー10のマップオブジェクトのポジション
	Vector3 layer10Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9]);
	// レイヤー10のスイッチ系マップオブジェクトのポジション
	Vector3 layer10SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer10)
	{
	case(LAYER10_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer10Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer10SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

/*
@fn レイヤー11クリエイター
@brief  レイヤー11のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer11(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer11 = layer11StageData[_indexY][_indexX];
	// レイヤー11のマップオブジェクトのポジション
	Vector3 layer11Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10]);
	// レイヤー11のスイッチ系マップオブジェクトのポジション
	Vector3 layer11SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer11)
	{
	case(LAYER11_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer11Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(TRACKING_ENEMY_PARTS):
		// 追跡する敵の生成
		new TrackingEnemyObject(layer11Pos, Tag::ENEMY, 600.0f, playerObject, 1400.0f);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer11SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer11SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	//case(SECOND_SWITCH_PARTS):
	//	// 第二区画スイッチオブジェクト生成
	//	new SwitchBaseObject(layer11SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
	//	break;

	//case(THIRD_STAGE_BACK_MOVE_GROUND):
	//	// 移動する床にのみ使うデータ構造体を作成
	//	SetMoveBlockData(Vector3(-1600.0f, 0.0f, 0.0f), Vector3::NegUnitX, 600.0f, MoveDirectionTag::MOVE_X);
	//	// 動く床を生成
	//	new MoveBlockObject(layer11Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
	//	break;


	}
}

/*
@fn レイヤー12クリエイター
@brief  レイヤー12のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer12(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer12 = layer12StageData[_indexY][_indexX];
	// レイヤー12のマップオブジェクトのポジション
	Vector3 layer12Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11]);
	// レイヤー12のスイッチ系マップオブジェクトのポジション
	Vector3 layer12SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer12)
	{
	case(LAYER12_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer12Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer12SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer12SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer12SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer12SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 左右に動く敵固有のデータ構造体をセット
		SetMoveEnemyData(600.0f, Vector3::UnitY, 1000.0f, MoveEnemyTag::RIGHT_MOVE);
		// 左右に動く敵の生成
		new MoveEnemyObject(layer12Pos, Tag::ENEMY, playerObject, moveEnemyData);
		break;
	}
}

/*
@fn レイヤー13クリエイター
@brief  レイヤー13のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer13(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer13 = layer13StageData[_indexY][_indexX];
	// レイヤー13のマップオブジェクトのポジション
	Vector3 layer13Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12]);
	// レイヤー13のスイッチ系マップオブジェクトのポジション
	Vector3 layer13SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer13)
	{
	case(LAYER13_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer13Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer13SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer13SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn レイヤー14クリエイター
@brief  レイヤー14のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer14(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer14 = layer14StageData[_indexY][_indexX];
	// レイヤー14のマップオブジェクトのポジション
	Vector3 layer14Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13]);
	// レイヤー14のスイッチ系マップオブジェクトのポジション
	Vector3 layer14SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer14)
	{
	case(LAYER14_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer14Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer14Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer14Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer14SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer14SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_FRONT_MOVE_GROUND):
		// 移動する床にのみ使うデータ構造体を作成
		SetMoveBlockData(Vector3(1600.0f, 0.0f, 0.0f), Vector3::UnitX, 600.0f, MoveDirectionTag::MOVE_X);
		// 移動床を生成
		new MoveBlockObject(layer14Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// 第二区画の動く壁オブジェクト生成
		lastMoveWallBlock = new MoveWallBlock(Vector3(layer14Pos.x, layer14Pos.y + ShiftMoveWallY, layer14Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer14Pos.x, layer14Pos.y, layer14Pos.z - BigMoveWallSize.z));
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer14Pos, Tag::ENEMY, playerObject);
		break;

	case(TRACKING_ENEMY_PARTS):
		// 追跡する敵の生成
		new TrackingEnemyObject(layer14Pos, Tag::ENEMY, 600.0f, playerObject, 1400.0f);
		break;
	}
}

/*
@fn レイヤー15クリエイター
@brief  レイヤー15のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer15(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer15 = layer15StageData[_indexY][_indexX];
	// レイヤー15のマップオブジェクトのポジション
	Vector3 layer15Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[14]);
	// レイヤー15のスイッチ系マップオブジェクトのポジション
	Vector3 layer15SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[14] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer15)
	{
	case(CLEAR_OBJECT_PARTS):
		// ステージクリアオブジェクト生成
		new NextSceneObject(Vector3(layer15Pos.x, layer15Pos.y, layer15Pos.z), Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;
	}
}

void ThirdStageCreator::CreateCameraDirecting(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int CameraDirectingData = cameraDirectingData[_indexY][_indexX];
	// レイヤー1のマップオブジェクトのポジション
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (CameraDirectingData)
	{
	case(38):
		AABB aabb = { Vector3(-3600.0f,-1800.0f,0.0f),Vector3(2000.0f,1800.0f,4000.0f) };
		// ブロックオブジェクト生成
		new CameraChangePoint(layer1Pos, aabb, Tag::CAMERA_CHANGE_BEHIND);
		break;
	}
}
