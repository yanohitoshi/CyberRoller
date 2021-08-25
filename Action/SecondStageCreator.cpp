//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SecondStageCreator.h"
#include "BoxObject.h"
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

/*
   @fn �R���X�g���N�^
   @brief block���m�̊Ԋu�̏�����(Offset)
*/
SecondStageCreator::SecondStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(12)
	, LightPointPositionZ(4800.0f)
{
}

/*
  @fn �f�X�g���N�^
*/
SecondStageCreator::~SecondStageCreator()
{
	//�}�b�v�f�[�^�̍폜
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

	playerData.clear();


}

bool SecondStageCreator::OpenFile()
{
	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/secondStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/secondStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/secondStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/secondStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/secondStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/secondStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/secondStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/secondStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/secondStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/secondStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/secondStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/secondStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (player) 
	if (!readTiledJson(playerData, "Assets/Config/secondStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	return false;

}

void SecondStageCreator::CreateStage()
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
			// Layer6��������
			CreateLayer6(ix, iy);
			// Layer7��������
			CreateLayer7(ix, iy);
			// Layer8��������
			CreateLayer8(ix, iy);
			// Layer9��������
			CreateLayer9(ix, iy);
			// Layer10��������
			CreateLayer10(ix, iy);
			// Layer11��������
			CreateLayer11(ix, iy);
			// Layer12��������
			CreateLayer12(ix, iy);
		}
	}

}

PlayerObject* SecondStageCreator::CreatePlayer()
{
	// �v���C���[�̈ʒu��񌟍�
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// �v���C���[�𐶐����鏈��
			ProductionPlayer(playerData[iy][ix], ix, iy);
		}
	}

	// �v���C���[�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return playerObject;
}

void SecondStageCreator::CreateLayer1(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer1 = layer1StageData[_indexY][_indexX];
	// ���C���[1�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer1)
	{
	case(LAYER1_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer1Pos, BlockSize, Tag::GROUND);
		break;
	}

}

void SecondStageCreator::CreateLayer2(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer2 = layer2StageData[_indexY][_indexX];
	// ���C���[2�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer2Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1]);
	// ���C���[2�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer2SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1] - ShiftSwitchPositionZ);

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
	}

}

void SecondStageCreator::CreateLayer3(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer3 = layer3StageData[_indexY][_indexX];
	// ���C���[3�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer3Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2]);
	// ���C���[3�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer3SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer3)
	{
	case(LAYER3_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer3Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer3SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer3SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

void SecondStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer4 = layer4StageData[_indexY][_indexX];
	// ���C���[4�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3]);
	// ���C���[4�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer4SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3] - ShiftSwitchPositionZ);
	
	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer4Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer4SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_STAGE_RIGHT_MOVE_GROUND):
		// �������𐶐�
		new MoveBlockObject(layer4Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, 1600.0f, 0.0f), Vector3::UnitY, 200.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void SecondStageCreator::CreateLayer5(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer5 = layer5StageData[_indexY][_indexX];
	// ���C���[5�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer5Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4]);
	// ���C���[5�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer5SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer5)
	{
	case(LAYER5_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer5Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer5SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(PORTRAIT_WALL_PARTS):
		// �c���ǃI�u�W�F�N�g�̐���
		new WallBlockObject(layer5Pos, PortraitWallBlockSize, Tag::WALL);
		break;

	case(LANDSCAPE_WALL_PARTS):
		// �����ǃI�u�W�F�N�g�̐���
		new WallBlockObject(layer5Pos, LandscapeWallBlockSize, Tag::WALL);
		break;
	}
}

void SecondStageCreator::CreateLayer6(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer6 = layer6StageData[_indexY][_indexX];
	// ���C���[6�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer6Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5]);
	// ���C���[6�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer6SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer6)
	{
	case(LAYER6_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer6Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer6SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer6Pos.x, layer6Pos.y + ShiftMoveWallY, layer6Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer6Pos.x, layer6Pos.y, layer6Pos.z - SmallMoveWallSize.z));
		break;

	case(SECOND_STAGE_RIGHT_MOVE_GROUND):
		// �������𐶐�
		new MoveBlockObject(layer6Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, 800.0f, 0.0f), Vector3::UnitY, 200.0f, MoveDirectionTag::MOVE_Y);
		break;

	case(SECOND_STAGE_LEFT_MOVE_GROUND):
		// �������𐶐�
		new MoveBlockObject(layer6Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, -800.0f, 0.0f), Vector3::NegUnitY, 350.0f, MoveDirectionTag::MOVE_Y);
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer6Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;
	}
}

void SecondStageCreator::CreateLayer7(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer7 = layer7StageData[_indexY][_indexX];
	// ���C���[7�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer7Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6]);
	// ���C���[7�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer7SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer7)
	{
	case(LAYER7_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer7Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer7SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer7SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer7Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;
	}
}

void SecondStageCreator::CreateLayer8(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer8 = layer8StageData[_indexY][_indexX];
	// ���C���[8�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer8Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7]);
	// ���C���[8�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer8SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer8)
	{
	case(LAYER8_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer8Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer8SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer8SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer8Pos.x, layer8Pos.y + ShiftMoveWallY, layer8Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer8Pos.x, layer8Pos.y, layer8Pos.z - SmallMoveWallSize.z));
		break;
	}
}

void SecondStageCreator::CreateLayer9(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer9 = layer9StageData[_indexY][_indexX];
	// ���C���[9�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer9Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer9)
	{
	case(LAYER9_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer9Pos, BlockSize, Tag::GROUND);
		break;
	}
}

void SecondStageCreator::CreateLayer10(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer10 = layer10StageData[_indexY][_indexX];
	// ���C���[10�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer10Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer10)
	{
	case(LAYER10_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer10Pos, BlockSize, Tag::GROUND);
		break;
	}
}

void SecondStageCreator::CreateLayer11(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer11 = layer11StageData[_indexY][_indexX];
	// ���C���[11�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer11Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer11)
	{
	case(LAYER11_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer11Pos, BlockSize, Tag::GROUND);
	}
}

void SecondStageCreator::CreateLayer12(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer12 = layer12StageData[_indexY][_indexX];
	// ���C���[12�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer12Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer12)
	{
	case(CLEAR_OBJECT_PARTS):
		// �X�e�[�W�N���A�I�u�W�F�N�g����
		new NextSceneObject(Vector3(layer12Pos.x, layer12Pos.y, layer12Pos.z), Tag::CLEAR_POINT, playerObject);
		break;
	}
}

