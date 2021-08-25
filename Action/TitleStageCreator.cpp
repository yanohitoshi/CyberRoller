//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
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
   @fn �R���X�g���N�^
   @brief block���m�̊Ԋu�̏�����(offset)
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
  @fn �f�X�g���N�^
 */
TitleStageCreator::~TitleStageCreator()
{
	//�}�b�v�f�[�^�̍폜
	titleMapData.clear();
	titlePlayerData.clear();
}

bool TitleStageCreator::OpenFile()
{

	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(titleMapData, "Assets/Config/TitleMap.json", "baselayer"))
	{
		printf("do'nt have Layer/Titlebaselayer\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = titleMapData[0].size();
	sizeY = titleMapData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (player)
	if (!readTiledJson(titlePlayerData, "Assets/Config/TitleMap.json", "player"))
	{
		printf("do'nt have Layer/Titleplayer\n");
		return true;
	}

	return false;
}

void TitleStageCreator::CreateStage()
{
	// ���N���X�Ƀv���C���[�̃|�W�V�����𑗂邽�߂̕ϐ�
	Vector3 sendPlayerPos = Vector3::Zero;

	// �v���C���[�̃X�e�[�W�f�[�^�����Ă��̏�񂲂Ƃ�class�𐶐�����
	// ��Ƀv���C���[�̃|�W�V�������m�肳���Ă��̌セ�̃|�W�V�����𑼃N���X�ɑ��肽���̂�
	// �v���C���[�̈ʒu�f�[�^���񂵐؂��Ă��܂�
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// �v���C���[�����֐�
			sendPlayerPos = CreatePlayer(ix,iy);
		}
	}

	// �X�e�[�W�f�[�^�����Ă��̏�񂲂Ƃ�class�𐶐�����
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// �^�C�g���p�}�b�v�X�e�[�W�����֐�
			CreateTitleMap(ix, iy, sendPlayerPos);
		}
	}

	// �^�C�g���p�J��������
	GameObject::CreateTitleCamera(sendPlayerPos);

}

void TitleStageCreator::CreateTitleMap(int _indexX, int _indexY,Vector3 _playerPos)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int baseLayer = titleMapData[(int)_indexY][(int)_indexX];
	// �^�C�g���X�e�[�W�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 baseLayerPos = Vector3(Offset * _indexX, -Offset * _indexY, TitleBlockPositionZ);

	// �}�b�v�f�[�^�������i���o�[��������
	if (baseLayer == GroundNumber)
	{
		// �^�C�g���p�I�u�W�F�N�g�̐���
		new TitleGroundObject(baseLayerPos, BlockSize, _playerPos,Tag::TITLE_OBJECT);
	}
}

Vector3 TitleStageCreator::CreatePlayer(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int playerLayer = titlePlayerData[(int)_indexY][(int)_indexX];
	// �^�C�g���ł̃v���C���[�I�u�W�F�N�g�̃|�W�V����
	Vector3 objectPos = Vector3(Offset * _indexX, -Offset * _indexY, TitlePlayerPositionZ);
	
	// �}�b�v�f�[�^�������i���o�[��������
	if (playerLayer == PlayerNumber)
	{
		// �^�C�g���p�v���C���[�̐���
		new TitlePlayerObject(objectPos, false, Tag::TITLE_PLAYER);
		// �|�W�V������ۑ�
		playerPos = objectPos;
	}

	// �v���C���[�̃|�W�V������Ԃ�
	return playerPos;

}
