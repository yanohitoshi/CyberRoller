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
   @fn �R���X�g���N�^
   @brief block���m�̊Ԋu�̏�����(offset)
 */

FirstStageCreator::FirstStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
{
}

/*
  @fn �f�X�g���N�^
 */

FirstStageCreator::~FirstStageCreator()
{
	//�}�b�v�f�[�^�̌�n��
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	playerData.clear();

}

bool FirstStageCreator::OpenFile()
{
	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/firstStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/firstStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/firstStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/firstStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/firstStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (player) 
	if (!readTiledJson(playerData, "Assets/Config/firstStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	return false;
}

PlayerObject* FirstStageCreator::CreatePlayer()
{
	//player�N���X�ɏ����ʒu��n�����߂̕ϐ�����
	Vector3 pos = Vector3(0, 0, 0);

	// �v���C���[�̈ʒu��񌟍�
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// �v���C���[�f�[�^���Ƀv���C���[������񂪂����
			if (playerData[iy][ix] == 19)
			{
				// �z��̓Y�����ƃI�u�W�F�N�g���Ƃ̊Ԋu��p���ă|�W�V������ݒ�
				pos = Vector3(Offset * ix, -Offset * iy, 500);
			}
		}
	}

	// �v���C���[�I�u�W�F�N�g����
	playerObject = new PlayerObject(pos, false, Tag::PLAYER);

	// ���C���J���������Ɠ����Ƀv���C���[�I�u�W�F�N�g�̃|�C���^��n��
	GameObject::CreateMainCamera(pos, playerObject);

	// �v���C���[�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return playerObject;
}

void FirstStageCreator::CreateStage()
{
	// �X�e�[�W�f�[�^�����Ă��̏�񂲂Ƃ�class�𐶐�����
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// Layer1��������
			CreateLayer1(ix, iy);
			// Layer2��������
			CreateLayer2(ix, iy);
			// Layer3��������
			CreateLayer3(ix, iy);
			// Layer4��������
			CreateLayer4(ix, iy);
			// Layer5��������
			CreateLayer5(ix, iy);
		}
	}
}

void FirstStageCreator::CreateLayer1(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer1 = layer1StageData[_indexY][_indexX];
	// ���C���[1�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, 0.0f);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer1)
	{
	case(LAYER1_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer1Pos, BlockSize, Tag::GROUND);
		break;
	}

}

void FirstStageCreator::CreateLayer2(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer2 = layer2StageData[_indexY][_indexX];
	// ���C���[2�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer2Pos = Vector3(Offset * _indexX, -Offset * _indexY, 200.0f);
	// ���C���[2�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer2SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 100.0f);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer2)
	{
	case(LAYER2_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer2Pos, BlockSize, Tag::GROUND);
		break;
	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer2SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer2SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}

}

void FirstStageCreator::CreateLayer3(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer3 = layer3StageData[_indexY][_indexX];
	// ���C���[3�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer3Pos = Vector3(Offset * _indexX, -Offset * _indexY, 400.0f);
	// ���C���[3�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer3SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 300.0f);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer3)
	{
	case(LAYER3_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer3Pos, BlockSize, Tag::GROUND);
		break;
	case(PORTRAIT_WALL_PARTS):
		// �c���ǃI�u�W�F�N�g�̐���
		new WallBlockObject(layer3Pos, PortraitWallBlockSize, Tag::WALL);
		break;
	case(LANDSCAPE_WALL_PARTS):
		// �����ǃI�u�W�F�N�g�̐���
		new WallBlockObject(layer3Pos, LandscapeWallBlockSize, Tag::WALL);
		break;
	}

}

void FirstStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer4 = layer4StageData[_indexY][_indexX];
	// ���C���[4�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, 600.0f);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer4Pos, BlockSize, Tag::GROUND);
		break;
	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer4Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	}

}

void FirstStageCreator::CreateLayer5(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer5 = layer5StageData[_indexY][_indexX];
	// ���C���[5�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer5Pos = Vector3(Offset * _indexX, -Offset * _indexY, 800.0f);
	// ���C���[5�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer5SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 700.0f);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer5)
	{
	case(LAYER5_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer5Pos, BlockSize, Tag::GROUND);
		break;
	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::TUTORIAL_SWITCH);
		break;
	case(CLEAR_OBJECT_PARTS):
		// �X�e�[�W�N���A�I�u�W�F�N�g����
		new NextSceneObject(Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z), Tag::TUTORIAL_CLEAR_POINT, playerObject);
		break;
	case(FIRST_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + ShiftMoveWallY, layer5Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::TUTORIAL_MOVE_WALL, MoveWallSpeed,
			Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - SmallMoveWallSize.z));
		break;
	}
}
