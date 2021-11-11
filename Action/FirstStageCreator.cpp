//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FirstStageCreator.h"
#include "AutoMoveCamera.h"
#include "CameraChangePoint.h"
#include "PlayerObject.h"
#include "GroundObject.h"
#include "BreakBlockObject.h"
#include "MoveWallBlock.h"
#include "LightObject.h"
#include "SwitchBaseObject.h"
#include "JumpSwitchObject.h"
#include "NeedlePanelObject.h"
#include "NextSceneObject.h"
#include "RespawnPoint.h"
#include "NormalEnemyObject.h"
#include "MoveEnemyObject.h"
#include "ExplosionObject.h"
#include "CollectionObject.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
@param	_reUseGameObject 再利用するかどうかフラグ
@param	_objectTag オブジェクト判別用Tag
*/
FirstStageCreator::FirstStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(5)
	, LightPointPositionZ(3000.0f)
{
}

/*
@fn デストラクタ
@brief マップデータの削除を行う
*/
FirstStageCreator::~FirstStageCreator()
{
	//マップデータの後始末
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	cameraDirectingData.clear();
	playerData.clear();
}

/*
@fn ファイルを開く
@return 成功か否か
*/
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

	// ステージデータ読み込み (CameraDirecting)
	if (!readTiledJson(cameraDirectingData, "Assets/Config/firstStageMap.json", "CameraDirecting"))
	{
		printf("do'nt have Layer/CameraDirecting\n");
		return true;
	}

	return false;
}

/*
@fn ステージを生成する
*/
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

void FirstStageCreator::CreateCamera()
{
}

/*
@fn プレイヤーを生成する
*/
PlayerObject* FirstStageCreator::CreatePlayer()
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
void FirstStageCreator::CreateLayer1(int _indexX, int _indexY)
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
	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer1Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}

}

/*
@fn レイヤー2クリエイター
@brief  レイヤー2のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void FirstStageCreator::CreateLayer2(int _indexX, int _indexY)
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
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND,true);
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

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer2Pos, BlockSize,Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn レイヤー3クリエイター
@brief  レイヤー3のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void FirstStageCreator::CreateLayer3(int _indexX, int _indexY)
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

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵を生成
		new NormalEnemyObject(layer3Pos, Tag::ENEMY, playerObject);
		break;

	case(BOMB_PARTS):
		new ExplosionObject(layer3Pos, Tag::BOMB);
		break;

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer3Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn レイヤー4クリエイター
@brief  レイヤー4のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void FirstStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer4 = layer4StageData[_indexY][_indexX];
	// レイヤー4のマップオブジェクトのポジション
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3]);

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

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer4Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;
	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer4Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn レイヤー5クリエイター
@brief  レイヤー5のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void FirstStageCreator::CreateLayer5(int _indexX, int _indexY)
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
	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// 第一区画の動く壁オブジェクト生成
		lastMoveWallBlock = new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + ShiftMoveWallY, layer5Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - SmallMoveWallSize.z));
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH,true);
		break;

	case(CLEAR_OBJECT_PARTS):
		// ステージクリアオブジェクト生成
		new NextSceneObject(Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z), Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer5Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵を生成
		new NormalEnemyObject(layer5Pos, Tag::ENEMY, playerObject);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 左右に動く敵固有のデータ構造体をセット
		SetMoveEnemyData(100.0f, Vector3::UnitY, 400.0f, MoveEnemyTag::RIGHT_MOVE);
		// 左右に動く敵を生成
		new MoveEnemyObject(layer5Pos, Tag::ENEMY, playerObject, moveEnemyData);
		break;

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer5Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

void FirstStageCreator::CreateCameraDirecting(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int CameraDirectingData = cameraDirectingData[_indexY][_indexX];
	// レイヤー1のマップオブジェクトのポジション
	Vector3 cameraPos = Vector3(Offset * _indexX, -Offset * _indexY, 3000.0f);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (CameraDirectingData)
	{
	case(17):
		// メインカメラ生成と同時にプレイヤーオブジェクトのポインタを渡す
		GameObject::CreateMainCamera(cameraPos, playerObject);
		break;
	}
}
