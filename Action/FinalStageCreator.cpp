//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FinalStageCreator.h"
#include "BoxObject.h"
#include "SwitchBlock.h"
#include "JumpSwitchObject.h"
#include "WallBlockObject.h"
#include "MoveWallBlock.h"
#include "PlayerObject.h"
#include "NextSceneObject.h"
#include "ClearPointObject.h"
#include "RespawnPoint.h"
#include "NeedlePanelObject.h"
#include "MoveBlockObject.h"
#include "PushBoxObject.h"
#include "SwitchBaseObject.h"

/*
   @fn �R���X�g���N�^
   @brief block���m�̊Ԋu�̏�����(Offset)
*/
FinalStageCreator::FinalStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(17)
	, LightPointPositionZ(7000.0f)
{
}

/*
  @fn �f�X�g���N�^
*/
FinalStageCreator::~FinalStageCreator()
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
	layer12StageData.clear();
	layer13StageData.clear();
	layer14StageData.clear();
	layer15StageData.clear();
	layer16StageData.clear();
	layer17StageData.clear();

	//�v���C���[�̃}�b�v�f�[�^�폜
	playerData.clear();

}

bool FinalStageCreator::OpenFile()
{
	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/finalStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/finalStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/finalStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/finalStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/finalStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/finalStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/finalStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/finalStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/finalStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer9\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/finalStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/finalStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/finalStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer13) 
	if (!readTiledJson(layer13StageData, "Assets/Config/finalStageMap.json", "layer13"))
	{
		printf("do'nt have Layer/layer13\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer14) 
	if (!readTiledJson(layer14StageData, "Assets/Config/finalStageMap.json", "layer14"))
	{
		printf("do'nt have Layer/layer14\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer15) 
	if (!readTiledJson(layer15StageData, "Assets/Config/finalStageMap.json", "layer15"))
	{
		printf("do'nt have Layer/layer15\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer16) 
	if (!readTiledJson(layer16StageData, "Assets/Config/finalStageMap.json", "layer16"))
	{
		printf("do'nt have Layer/layer16\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer17) 
	if (!readTiledJson(layer17StageData, "Assets/Config/finalStageMap.json", "layer17"))
	{
		printf("do'nt have Layer/layer17\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (player) 
	if (!readTiledJson(playerData, "Assets/Config/finalStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}


	return false;
}

void FinalStageCreator::CreateStage()
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
			// Layer13��������
			CreateLayer13(ix, iy);
			// Layer14��������
			CreateLayer14(ix, iy);
			// Layer15��������
			CreateLayer15(ix, iy);
			// Layer16��������
			CreateLayer16(ix, iy);
			// Layer17��������
			CreateLayer17(ix, iy);
		}
	}
}

PlayerObject* FinalStageCreator::CreatePlayer()
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

void FinalStageCreator::CreateLayer1(int _indexX, int _indexY)
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

void FinalStageCreator::CreateLayer2(int _indexX, int _indexY)
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
		break;
	}
}

void FinalStageCreator::CreateLayer3(int _indexX, int _indexY)
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

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer3SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

void FinalStageCreator::CreateLayer4(int _indexX, int _indexY)
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

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer4SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(LEFT_MOVE_GROUND_NUMBER_1):
		new MoveBlockObject(layer4Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, -1600.0f, 0.0f), Vector3::NegUnitY, 400.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer5(int _indexX, int _indexY)
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
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer5SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer5SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + ShiftMoveWallY, layer5Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - BigMoveWallSize.z));
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer5Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(LEFT_PUSH_BOX_NUMBER_1):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(LEFT_PUSH_BOX_NUMBER_2):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1450.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(LEFT_PUSH_BOX_NUMBER_3):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1400.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(LEFT_PUSH_BOX_NUMBER_4):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1300.0f, 0.2f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_1):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_2):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1450.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_3):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1400.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_4):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1300.0f, 0.2f, MoveDirectionTag::MOVE_Y);
		break;

	case(FRONT_MOVE_GROUND_NUMBER_1):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(1400.0f, 0.0f, 0.0f), Vector3::UnitX, 400.0f, MoveDirectionTag::MOVE_X);
		break;

	case(BACK_MOVE_GROUND_NUMBER_1):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(-1600.0f, 0.0f, 0.0f), Vector3::NegUnitX, 400.0f, MoveDirectionTag::MOVE_X);
		break;

	case(FRONT_MOVE_GROUND_NUMBER_3):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(1600.0f, 0.0f, 0.0f), Vector3::UnitX, 800.0f, MoveDirectionTag::MOVE_X);
		break;

	case(BACK_MOVE_GROUND_NUMBER_2):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(-1600.0f, 0.0f, 0.0f), Vector3::NegUnitX, 800.0f, MoveDirectionTag::MOVE_X);
		break;

	case(LEFT_MOVE_GROUND_NUMBER_2):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, -1400.0f, 0.0f), Vector3::NegUnitY, 700.0f, MoveDirectionTag::MOVE_Y);
		break;

	case(RIGHT_MOVE_GROUND_NUMBER_1):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, 1400.0f, 0.0f), Vector3::UnitY, 700.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer6(int _indexX, int _indexY)
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

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer6SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer6SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(LEFT_PUSH_BOX_NUMBER_5):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer6Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1200.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;
		
	case(RIGHT_PUSH_BOX_NUMBER_5):
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer6Pos, BlockSize, Tag::PUSH_BOX, Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1800.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer7(int _indexX, int _indexY)
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

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer7SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(LEFT_MOVE_GROUND_NUMBER_3):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer7Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, -800.0f, 0.0f), Vector3::NegUnitY, 400.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer8(int _indexX, int _indexY)
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
		new SwitchBaseObject(layer8SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer8SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer8SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(RIGHT_MOVE_GROUND_NUMBER_2):
		// �P�[�X���Ƃɕ����̈Ⴄ�������𐶐�
		new MoveBlockObject(layer8Pos, BlockSize, Tag::MOVE_GROUND, Vector3(0.0f, 800.0f, 0.0f), Vector3::UnitY, 400.0f, MoveDirectionTag::MOVE_Y);
		break;
	}
}

void FinalStageCreator::CreateLayer9(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer9 = layer9StageData[_indexY][_indexX];
	// ���C���[9�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer9Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8]);
	// ���C���[9�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer9SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer9)
	{
	case(LAYER9_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer9Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer9SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer9SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

void FinalStageCreator::CreateLayer10(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer10 = layer10StageData[_indexY][_indexX];
	// ���C���[10�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer10Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9]);
	// ���C���[10�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer10SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer10)
	{
	case(LAYER10_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer10Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer10SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer10Pos.x, layer10Pos.y + ShiftMoveWallY, layer10Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::SECOND_MOVE_WALL, MoveWallSpeed,
			Vector3(layer10Pos.x, layer10Pos.y, layer10Pos.z - BigMoveWallSize.z));
		break;
	}
}

void FinalStageCreator::CreateLayer11(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer11 = layer11StageData[_indexY][_indexX];
	// ���C���[11�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer11Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10]);
	// ���C���[11�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer11SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer11)
	{
	case(LAYER11_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer11Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer11SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer11SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer11SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

void FinalStageCreator::CreateLayer12(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer12 = layer12StageData[_indexY][_indexX];
	// ���C���[12�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer12Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11]);
	// ���C���[12�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer12SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer12)
	{
	case(LAYER12_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer12Pos, BlockSize, Tag::GROUND);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer12SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer12SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

void FinalStageCreator::CreateLayer13(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer13 = layer13StageData[_indexY][_indexX];
	// ���C���[13�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer13Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12]);
	// ���C���[13�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer13SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer13)
	{
	case(LAYER13_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer13Pos, BlockSize, Tag::GROUND);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer13SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer13SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

void FinalStageCreator::CreateLayer14(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer14 = layer14StageData[_indexY][_indexX];
	// ���C���[14�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer14Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13]);
	// ���C���[14�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer14SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer14)
	{
	case(LAYER14_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer14Pos, BlockSize, Tag::GROUND);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer14SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer14SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(THIRD_MOVE_WALL_PARTS):
		// ��O���̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer14Pos.x, layer14Pos.y + ShiftMoveWallY, layer14Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer14Pos.x, layer14Pos.y, layer14Pos.z - BigMoveWallSize.z));
		break;
	}
}

void FinalStageCreator::CreateLayer15(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer15 = layer15StageData[_indexY][_indexX];
	// ���C���[8�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer15Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[14]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer15)
	{
	case(LAYER15_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer15Pos, BlockSize, Tag::GROUND);
		break;
	}
}

void FinalStageCreator::CreateLayer16(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer16 = layer16StageData[_indexY][_indexX];
	// ���C���[16�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer16Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[15]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer16)
	{
	case(LAYER16_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer16Pos, BlockSize, Tag::GROUND);
		break;
	}
}

void FinalStageCreator::CreateLayer17(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int layer17 = layer17StageData[_indexY][_indexX];
	// ���C���[17�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer17Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[16]);
	// ���C���[17�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer17SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, 3101.0f);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (layer17)
	{
	case(LAYER17_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new BoxObject(layer17Pos, BlockSize, Tag::GROUND);
		break;

	case(CLEAR_OBJECT_PARTS):
		// �X�e�[�W�N���A�I�u�W�F�N�g����
		new ClearPointObject(Vector3(layer17Pos.x, layer17Pos.y, layer17Pos.z), Tag::CLEAR_POINT, playerObject);
		break;
	}
}

