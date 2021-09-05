#include "ResultSceneCreator.h"
#include "ResultSwitchBaseObject.h"
#include "ResultCameraObject.h"
/*
   @fn コンストラクタ
   @brief block同士の間隔の初期化(offset)
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
 */
ResultSceneCreator::~ResultSceneCreator()
{
	//マップデータの削除
	resultMapData.clear();
	resultCameraData.clear();
}

bool ResultSceneCreator::OpenFile()
{

	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(resultMapData, "Assets/Config/ResultScene.json", "BaseLayer"))
	{
		printf("do'nt have Layer/BaseLayer\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = resultMapData[0].size();
	sizeY = resultMapData.size();

	// ステージデータ読み込み (CameraTarget)
	if (!readTiledJson(resultCameraData, "Assets/Config/ResultScene.json", "CameraTarget"))
	{
		printf("do'nt have Layer/CameraTarget\n");
		return true;
	}

	return false;
}

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

void ResultSceneCreator::CreateResultMap(int _indexX, int _indexZ)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int baseLayer = resultMapData[(int)_indexZ][(int)_indexX];
	// リザルトステージのマップオブジェクトのポジション
	Vector3 resultBaseLayerPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// マップデータが生成ナンバーだったら
	if (baseLayer == SwitchNumber)
	{
		// タイトル用オブジェクトの生成
		new ResultSwitchBaseObject(resultBaseLayerPos, SwitchBaseSize, Tag::RESULT_OBJECT,Tag::RESULT_OBJECT);
	}
}

void ResultSceneCreator::CreateCamera(int _indexX, int _indexZ)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int cameraTarget = resultCameraData[(int)_indexZ][(int)_indexX];
	// タイトルでのプレイヤーオブジェクトのポジション
	Vector3 objectPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// マップデータが生成ナンバーだったら
	if (cameraTarget == CameraNumber)
	{
		new ResultCameraObject(objectPos);
	}
}
