//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"
#include "PlayerObject.h"

StageCreatorBase::StageCreatorBase(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, BlockSize(Vector3(200.0f, 200.0f, 100.0f))
	, SwitchBaseSize(Vector3(2.0f, 2.0f, 1.0f))
	, NeedlePanelSize(Vector3(200.0f, 200.0f, 3.0f))
	, JumpSwitchSize(Vector3(200.0f, 200.0f, 3.0f))
	, PortraitWallBlockSize(Vector3(600.0f, 200.0f, 2400.0f))
	, LandscapeWallBlockSize(Vector3(200.0f, 600.0f, 2400.0f))
	, BigMoveWallSize(Vector3(20.0f, 1500.0f, 1000.0f))
	, SmallMoveWallSize(Vector3(20.0f, 1100.0f, 1000.0f))
	, RespawnBox({ Vector3(-10.0f,-1000.0f,-2000.0f),Vector3(10.0f,1000.0f,2000.0f) })
	, LightPointBox({ Vector3(-10.0f,-2000.0f,-10000.0f),Vector3(10.0f,2000.0f,10000.0f) })
	, Offset(400.0f)
	, OffsetZ(200.0f)
	, ShiftMoveWallY(200.0f)
	, ShiftMoveWallZ(100.0f)
	, MoveWallSpeed(300.0f)
	, ShiftSwitchPositionZ(100.0f)
	, PlayerPositionZ(500.0f)
	, MaxLayer(17)
	, lastMoveWallBlock(nullptr)
{
	// レイヤーのZ軸ポジションの初期化
	for (int layer = 0; layer < MaxLayer; layer++)
	{
		// ブロック系のオブジェクトの高さの間隔は200.0fなのでそれに準じてレイヤーの最大数で初期化
		objectPositionZ[layer] = layer * OffsetZ;
	}
}

/*
@fn デストラクタ
*/
StageCreatorBase::~StageCreatorBase()
{
}

/*
@fn JSONfileを読み込み(読む)
@brief OpenFileで開いたデータを読み込み必要な配列データを取得
@param std::vector<std::vector<int>>& _mapData　配列データを受け取るための配列
@param const char* _filename どのfileを読むかを指定するためのcharポインタ
@param const char* _layername どのlayerを読むかを指定するためのcharポインタ
@return true or false (成功か失敗)
*/
bool StageCreatorBase::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _filename, const char* _layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc, _filename))
	{
		return false;
	}

	// 開いたDocmentのtype は mapか？
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}

	// 開いたDocumentにlayerはあるか？
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}
	// layer数取得
	auto layer = doc["layers"].GetArray();
	int  layerSize = layer.Size();

	// レイヤー名から該当レイヤーの添え字値を調べる
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	// layer内にdataはある？    
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", _layerName);
		return false;
	}

	// レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	// ユーザー配列確保 行方向、列方向の順番にサイズ確保
	_mapData.resize(height);
	for (auto& mapIter : _mapData)
	{
		mapIter.resize(width);
	}

	// ユーザー配列（2次元）にデータをコピーする
	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			// なぜか IDが +1ずれているので補正する 
			_mapData[z][x] = rapidArrayData[z * width + x].GetInt();
		}
	}

	return true;
}

int StageCreatorBase::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName)
{
	int  layerSize = layer.Size();

	int i;
	std::string layerNameString(layerName);
	for (i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = layer[i]["name"].GetString();
		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}
	return i;
}

void StageCreatorBase::ProductionPlayer(int _data, int _indexX, int _indexY)
{
	// プレイヤーデータ内にプレイヤー生成情報があれば
	if (_data == PLAYER_PARTS)
	{
		Vector3 pos = Vector3::Zero;

		// 配列の添え字とオブジェクトごとの間隔を用いてポジションを設定
		pos = Vector3(Offset * _indexX, -Offset * _indexY, PlayerPositionZ);
		// プレイヤーオブジェクト生成
		playerObject = new PlayerObject(pos, false, Tag::PLAYER);

		// メインカメラ生成と同時にプレイヤーオブジェクトのポインタを渡す
		GameObject::CreateMainCamera(pos, playerObject);

	}

}



