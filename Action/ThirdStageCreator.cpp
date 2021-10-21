//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
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
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_reUseGameObject �ė��p���邩�ǂ����t���O
@param	_objectTag �I�u�W�F�N�g���ʗpTag
*/
ThirdStageCreator::ThirdStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(15)
	, LightPointPositionZ(7000.0f)
{
}

/*
@fn �f�X�g���N�^
@brief �}�b�v�f�[�^�̍폜���s��
*/
ThirdStageCreator::~ThirdStageCreator()
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
	cameraDirectingData.clear();
	// �v���C���[�̃}�b�v�f�[�^�폜
	playerData.clear();
}

/*
@fn �t�@�C�����J��
@return �������ۂ�
*/
bool ThirdStageCreator::OpenFile()
{
	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/thirdStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/thirdStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/thirdStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/thirdStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/thirdStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/thirdStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/thirdStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/thirdStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/thirdStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer9\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/thirdStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/thirdStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/thirdStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer13) 
	if (!readTiledJson(layer13StageData, "Assets/Config/thirdStageMap.json", "layer13"))
	{
		printf("do'nt have Layer/layer13\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer14) 
	if (!readTiledJson(layer14StageData, "Assets/Config/thirdStageMap.json", "layer14"))
	{
		printf("do'nt have Layer/layer14\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer15) 
	if (!readTiledJson(layer15StageData, "Assets/Config/thirdStageMap.json", "layer15"))
	{
		printf("do'nt have Layer/layer15\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (player) 
	if (!readTiledJson(playerData, "Assets/Config/thirdStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (CameraDirecting)
	if (!readTiledJson(cameraDirectingData, "Assets/Config/thirdStageMap.json", "CameraDirecting"))
	{
		printf("do'nt have Layer/CameraDirecting\n");
		return true;
	}

	return false;
}

/*
@fn �X�e�[�W�𐶐�����
*/
void ThirdStageCreator::CreateStage()
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
			CreateCameraDirecting(ix, iy);
		}
	}
}

/*
@fn �v���C���[�𐶐�����
*/
PlayerObject* ThirdStageCreator::CreatePlayer()
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

/*
@fn ���C���[1�N���G�C�^�[
@brief  ���C���[1�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer1(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer1 = layer1StageData[_indexY][_indexX];
	// ���C���[1�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer1)
	{
	case(LAYER1_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer1Pos, BlockSize, Tag::GROUND);
		break;
	}
}

/*
@fn ���C���[2�N���G�C�^�[
@brief  ���C���[2�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer2(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer2 = layer2StageData[_indexY][_indexX];
	// ���C���[2�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer2Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1]);
	// ���C���[2�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer2SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer2)
	{
	case(LAYER2_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer2Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer2SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	}

}

/*
@fn ���C���[3�N���G�C�^�[
@brief  ���C���[3�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer3(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer3 = layer3StageData[_indexY][_indexX];
	// ���C���[3�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer3Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2]);
	// ���C���[3�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer3SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer3)
	{
	case(LAYER3_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer3Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer3SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer3SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer3SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer3SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn ���C���[4�N���G�C�^�[
@brief  ���C���[4�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer4 = layer4StageData[_indexY][_indexX];
	// ���C���[4�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3]);
	// ���C���[4�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer4SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3] - ShiftSwitchPositionZ);
	
	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer4Pos, BlockSize, Tag::GROUND);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer4SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn ���C���[5�N���G�C�^�[
@brief  ���C���[5�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer5(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer5 = layer5StageData[_indexY][_indexX];
	// ���C���[5�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer5Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4]);
	// ���C���[5�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer5SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer5)
	{
	case(LAYER5_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer5Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, false);
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

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer5SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_FRONT_MOVE_GROUND):
		// �ړ����鏰�ɂ̂ݎg���f�[�^�\���̂��쐬
		SetMoveBlockData(Vector3(1200.0f, 0.0f, 0.0f), Vector3::UnitX, 300.0f, MoveDirectionTag::MOVE_X);
		// �������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(THIRD_STAGE_BACK_MOVE_GROUND):
		// �ړ����鏰�ɂ̂ݎg���f�[�^�\���̂��쐬
		SetMoveBlockData(Vector3(-800.0f, 0.0f, 0.0f), Vector3::NegUnitX, 300.0f, MoveDirectionTag::MOVE_X);
		// �������𐶐�
		new MoveBlockObject(layer5Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer5Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;
	}
}

/*
@fn ���C���[6�N���G�C�^�[
@brief  ���C���[6�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer6(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer6 = layer6StageData[_indexY][_indexX];
	// ���C���[6�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer6Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5]);
	// ���C���[6�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer6SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer6)
	{
	case(LAYER6_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer6Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer6Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer6Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer6SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer6SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer6SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_LEFT_MOVE_GROUND):
		// �ړ����鏰�ɂ̂ݎg���f�[�^�\���̂��쐬
		SetMoveBlockData(Vector3(0.0f, -1400.0f, 0.0f), Vector3::NegUnitY, 300.0f, MoveDirectionTag::MOVE_Y);
		// �ړ����鏰�𐶐�
		new MoveBlockObject(layer6Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(TRACKING_ENEMY_PARTS):
		new TrackingEnemyObject(layer6Pos, Tag::ENEMY, 600.0f, playerObject, 1200.0f);
		break;

	case(RIGHT_PUSH_BOX):
		// �v�b�V���{�[�h�ŗL�̃f�[�^�\���̂��Z�b�g
		SetPushBoxData(Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// �P�[�X���Ƃɕ����̈Ⴄ�����o���{�b�N�X�̐���
		new PushBoxObject(layer6Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;
	}
}

/*
@fn ���C���[7�N���G�C�^�[
@brief  ���C���[7�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer7(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer7 = layer7StageData[_indexY][_indexX];
	// ���C���[7�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer7Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6]);
	// ���C���[7�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer7SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer7)
	{
	case(LAYER7_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer7Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer7Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer7Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer7SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer7SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_RIGHT_MOVE_GROUND):
		// �ړ����鏰�ɂ̂ݎg���f�[�^�\���̂��쐬
		SetMoveBlockData(Vector3(0.0f, 1400.0f, 0.0f), Vector3::UnitY, 300.0f, MoveDirectionTag::MOVE_Y);
		// �������̐���
		new MoveBlockObject(layer7Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(NORMAL_ENEMY_PARTS):
		// �����Ȃ��G�̐���
		new NormalEnemyObject(layer7Pos, Tag::ENEMY, playerObject);
		break;
	}
}

/*
@fn ���C���[8�N���G�C�^�[
@brief  ���C���[8�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer8(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer8 = layer8StageData[_indexY][_indexX];
	// ���C���[8�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer8Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7]);
	// ���C���[8�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer8SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer8)
	{
	case(LAYER8_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer8Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer8SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer8SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer8SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn ���C���[9�N���G�C�^�[
@brief  ���C���[9�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer9(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer9 = layer9StageData[_indexY][_indexX];
	// ���C���[9�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer9Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8]);
	// ���C���[9�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer9SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer9)
	{
	case(LAYER9_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer9Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer9Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer9Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer9SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer9Pos.x, layer9Pos.y + ShiftMoveWallY, layer9Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer9Pos.x, layer9Pos.y, layer9Pos.z - BigMoveWallSize.z));
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer9Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer9SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(TRACKING_ENEMY_PARTS):
		// �ǐՂ���G�̐���
		new TrackingEnemyObject(layer9Pos, Tag::ENEMY, 600.0f, playerObject,1400.0f);
		break;

	case(NORMAL_ENEMY_PARTS):
		// �����Ȃ��G�̐���
		new NormalEnemyObject(layer9Pos, Tag::ENEMY, playerObject);
		break;
	}
}

/*
@fn ���C���[10�N���G�C�^�[
@brief  ���C���[10�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer10(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer10 = layer10StageData[_indexY][_indexX];
	// ���C���[10�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer10Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9]);
	// ���C���[10�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer10SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer10)
	{
	case(LAYER10_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer10Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer10SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer10SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;
	}
}

/*
@fn ���C���[11�N���G�C�^�[
@brief  ���C���[11�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer11(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer11 = layer11StageData[_indexY][_indexX];
	// ���C���[11�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer11Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10]);
	// ���C���[11�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer11SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer11)
	{
	case(LAYER11_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer11Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(TRACKING_ENEMY_PARTS):
		// �ǐՂ���G�̐���
		new TrackingEnemyObject(layer11Pos, Tag::ENEMY, 600.0f, playerObject, 1400.0f);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer11SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer11SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	//case(SECOND_SWITCH_PARTS):
	//	// �����X�C�b�`�I�u�W�F�N�g����
	//	new SwitchBaseObject(layer11SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
	//	break;

	//case(THIRD_STAGE_BACK_MOVE_GROUND):
	//	// �ړ����鏰�ɂ̂ݎg���f�[�^�\���̂��쐬
	//	SetMoveBlockData(Vector3(-1600.0f, 0.0f, 0.0f), Vector3::NegUnitX, 600.0f, MoveDirectionTag::MOVE_X);
	//	// �������𐶐�
	//	new MoveBlockObject(layer11Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
	//	break;


	}
}

/*
@fn ���C���[12�N���G�C�^�[
@brief  ���C���[12�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer12(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer12 = layer12StageData[_indexY][_indexX];
	// ���C���[12�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer12Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11]);
	// ���C���[12�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer12SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer12)
	{
	case(LAYER12_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer12Pos, BlockSize, Tag::GROUND);
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer12SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer12SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer12SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer12SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// ���E�ɓ����G�ŗL�̃f�[�^�\���̂��Z�b�g
		SetMoveEnemyData(600.0f, Vector3::UnitY, 1000.0f, MoveEnemyTag::RIGHT_MOVE);
		// ���E�ɓ����G�̐���
		new MoveEnemyObject(layer12Pos, Tag::ENEMY, playerObject, moveEnemyData);
		break;
	}
}

/*
@fn ���C���[13�N���G�C�^�[
@brief  ���C���[13�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer13(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer13 = layer13StageData[_indexY][_indexX];
	// ���C���[13�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer13Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12]);
	// ���C���[13�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer13SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer13)
	{
	case(LAYER13_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer13Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer13SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer13SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;
	}
}

/*
@fn ���C���[14�N���G�C�^�[
@brief  ���C���[14�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer14(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer14 = layer14StageData[_indexY][_indexX];
	// ���C���[14�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer14Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13]);
	// ���C���[14�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer14SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer14)
	{
	case(LAYER14_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer14Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer14Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer14Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer14SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer14SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(THIRD_STAGE_FRONT_MOVE_GROUND):
		// �ړ����鏰�ɂ̂ݎg���f�[�^�\���̂��쐬
		SetMoveBlockData(Vector3(1600.0f, 0.0f, 0.0f), Vector3::UnitX, 600.0f, MoveDirectionTag::MOVE_X);
		// �ړ����𐶐�
		new MoveBlockObject(layer14Pos, BlockSize, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		lastMoveWallBlock = new MoveWallBlock(Vector3(layer14Pos.x, layer14Pos.y + ShiftMoveWallY, layer14Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer14Pos.x, layer14Pos.y, layer14Pos.z - BigMoveWallSize.z));
		break;

	case(NORMAL_ENEMY_PARTS):
		// �����Ȃ��G�̐���
		new NormalEnemyObject(layer14Pos, Tag::ENEMY, playerObject);
		break;

	case(TRACKING_ENEMY_PARTS):
		// �ǐՂ���G�̐���
		new TrackingEnemyObject(layer14Pos, Tag::ENEMY, 600.0f, playerObject, 1400.0f);
		break;
	}
}

/*
@fn ���C���[15�N���G�C�^�[
@brief  ���C���[15�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ThirdStageCreator::CreateLayer15(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer15 = layer15StageData[_indexY][_indexX];
	// ���C���[15�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer15Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[14]);
	// ���C���[15�̃X�C�b�`�n�}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer15SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[14] - ShiftSwitchPositionZ);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer15)
	{
	case(CLEAR_OBJECT_PARTS):
		// �X�e�[�W�N���A�I�u�W�F�N�g����
		new NextSceneObject(Vector3(layer15Pos.x, layer15Pos.y, layer15Pos.z), Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;
	}
}

void ThirdStageCreator::CreateCameraDirecting(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int CameraDirectingData = cameraDirectingData[_indexY][_indexX];
	// ���C���[1�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (CameraDirectingData)
	{
	case(38):
		AABB aabb = { Vector3(-3600.0f,-1800.0f,0.0f),Vector3(2000.0f,1800.0f,4000.0f) };
		// �u���b�N�I�u�W�F�N�g����
		new CameraChangePoint(layer1Pos, aabb, Tag::CAMERA_CHANGE_BEHIND);
		break;
	}
}
