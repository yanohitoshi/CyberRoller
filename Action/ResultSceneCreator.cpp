//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultSceneCreator.h"
#include "ResultSwitchBaseObject.h"
#include "ResultCameraObject.h"

/*
@fn コンストラクタ
@brief  objectの生成を行う
@param	_reUseGameObject 再利用するかどうかフラグ
@param	_objectTag オブジェクト判別用Tag
*/
ResultSceneCreator::ResultSceneCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, SwitchNumber(22)
	, CameraNumber(23)
	, ResultOffset(300.0f)
{
}

/*
@fn デストラクタ
@brief マップデータの削除を行う
*/
ResultSceneCreator::~ResultSceneCreator()
{
	//マップデータの削除
	resultMapData.clear();
	resultCameraData.clear();
}

/*
@fn ファイルを開く
@return 成功か否か
*/
bool ResultSceneCreator::OpenFile()
{

	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(resultMapData, "Assets/Config/StageData/ResultScene.json", "BaseLayer"))
	{
		printf("do'nt have Layer/BaseLayer\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = resultMapData[0].size();
	sizeY = resultMapData.size();

	// ステージデータ読み込み (CameraTarget)
	if (!readTiledJson(resultCameraData, "Assets/Config/StageData/ResultScene.json", "CameraTarget"))
	{
		printf("do'nt have Layer/CameraTarget\n");
		return true;
	}

	return false;
}

/*
@fn ステージを生成する
*/
void ResultSceneCreator::CreateStage()
{
	// 他クラスにプレイヤーのポジションを送るための変数
	Vector3 sendPlayerPos = Vector3::Zero;

	// カメラの生成
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// プレイヤー生成関数
			CreateCamera(ix, iy);
		}
	}

	// ステージデータを見てその情報ごとのclassを生成する
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// リザルトObjectの生成
			CreateResultMap(ix, iy);
		}
	}
}

/*
@fn baseLayerクリエイター
@brief  レイヤー1のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ResultSceneCreator::CreateResultMap(int _indexX, int _indexZ)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int BaseLayer = resultMapData[(int)_indexZ][(int)_indexX];
	// リザルトステージのマップオブジェクトのポジション
	Vector3 resultBaseLayerPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// マップデータが生成ナンバーだったら
	if (BaseLayer == SwitchNumber)
	{
		// タイトル用オブジェクトの生成
		new ResultSwitchBaseObject(resultBaseLayerPos, SwitchBaseSize, Tag::RESULT_OBJECT);
	}
}

/*
@fn CameraTargetクリエイター
@brief  レイヤー2のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ResultSceneCreator::CreateCamera(int _indexX, int _indexZ)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int CameraTarget = resultCameraData[(int)_indexZ][(int)_indexX];
	// タイトルでのプレイヤーオブジェクトのポジション
	Vector3 objectPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// マップデータが生成ナンバーだったら
	if (CameraTarget == CameraNumber)
	{
		new ResultCameraObject(objectPos);
	}
}