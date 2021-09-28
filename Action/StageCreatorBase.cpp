//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
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
	// ���C���[��Z���|�W�V�����̏�����
	for (int layer = 0; layer < MaxLayer; layer++)
	{
		// �u���b�N�n�̃I�u�W�F�N�g�̍����̊Ԋu��200.0f�Ȃ̂ł���ɏ����ă��C���[�̍ő吔�ŏ�����
		objectPositionZ[layer] = layer * OffsetZ;
	}
}

/*
@fn �f�X�g���N�^
*/
StageCreatorBase::~StageCreatorBase()
{
}

/*
@fn JSONfile��ǂݍ���(�ǂ�)
@brief OpenFile�ŊJ�����f�[�^��ǂݍ��ݕK�v�Ȕz��f�[�^���擾
@param std::vector<std::vector<int>>& _mapData�@�z��f�[�^���󂯎�邽�߂̔z��
@param const char* _filename �ǂ�file��ǂނ����w�肷�邽�߂�char�|�C���^
@param const char* _layername �ǂ�layer��ǂނ����w�肷�邽�߂�char�|�C���^
@return true or false (���������s)
*/
bool StageCreatorBase::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _filename, const char* _layerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc, _filename))
	{
		return false;
	}

	// �J����Docment��type �� map���H
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}

	// �J����Document��layer�͂��邩�H
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}
	// layer���擾
	auto layer = doc["layers"].GetArray();
	int  layerSize = layer.Size();

	// ���C���[������Y�����C���[�̓Y�����l�𒲂ׂ�
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	// layer����data�͂���H    
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _layerName);
		return false;
	}

	// ���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	// ���[�U�[�z��m�� �s�����A������̏��ԂɃT�C�Y�m��
	_mapData.resize(height);
	for (auto& mapIter : _mapData)
	{
		mapIter.resize(width);
	}

	// ���[�U�[�z��i2�����j�Ƀf�[�^���R�s�[����
	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			// �Ȃ��� ID�� +1����Ă���̂ŕ␳���� 
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
	// �v���C���[�f�[�^���Ƀv���C���[������񂪂����
	if (_data == PLAYER_PARTS)
	{
		Vector3 pos = Vector3::Zero;

		// �z��̓Y�����ƃI�u�W�F�N�g���Ƃ̊Ԋu��p���ă|�W�V������ݒ�
		pos = Vector3(Offset * _indexX, -Offset * _indexY, PlayerPositionZ);
		// �v���C���[�I�u�W�F�N�g����
		playerObject = new PlayerObject(pos, false, Tag::PLAYER);

		// ���C���J���������Ɠ����Ƀv���C���[�I�u�W�F�N�g�̃|�C���^��n��
		GameObject::CreateMainCamera(pos, playerObject);

	}

}



