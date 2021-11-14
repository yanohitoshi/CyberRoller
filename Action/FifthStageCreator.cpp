//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FifthStageCreator.h"
#include "PlayerObject.h"
#include "GroundObject.h"
#include "BreakBlockObject.h"
#include "LightObject.h"
#include "MoveBlockObject.h"
#include "MoveWallBlock.h"
#include "PushBoxObject.h"
#include "SwitchBaseObject.h"
#include "JumpSwitchObject.h"
#include "ExplosionObject.h"
#include "NeedlePanelObject.h"
#include "RespawnPoint.h"
#include "TrackingEnemyObject.h"
#include "NormalEnemyObject.h"
#include "MoveEnemyObject.h"
#include "EnhancedEnemyObject.h"
#include "CameraChangePoint.h"
#include "NextSceneObject.h"
#include "CollectionObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_reUseGameObject �ė��p���邩�ǂ����t���O
@param	_objectTag �I�u�W�F�N�g���ʗpTag
*/
FifthStageCreator::FifthStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(17)
	, LightPointPositionZ(7000.0f)
{
}

/*
@fn �f�X�g���N�^
@brief �}�b�v�f�[�^�̍폜���s��
*/
FifthStageCreator::~FifthStageCreator()
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

	cameraDirectingData.clear();
	//�v���C���[�̃}�b�v�f�[�^�폜
	playerData.clear();

}

/*
@fn �t�@�C�����J��
@return �������ۂ�
*/
bool FifthStageCreator::OpenFile()
{
	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/fifthStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/fifthStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/fifthStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/fifthStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/fifthStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/fifthStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/fifthStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/fifthStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/fifthStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer9\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/fifthStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/fifthStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/fifthStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}
	// �X�e�[�W�f�[�^�ǂݍ��� (layer13) 
	if (!readTiledJson(layer13StageData, "Assets/Config/fifthStageMap.json", "layer13"))
	{
		printf("do'nt have Layer/layer13\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (player) 
	if (!readTiledJson(playerData, "Assets/Config/fifthStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	// �X�e�[�W�f�[�^�ǂݍ��� (CameraDirecting)
	if (!readTiledJson(cameraDirectingData, "Assets/Config/fifthStageMap.json", "CameraDirecting"))
	{
		printf("do'nt have Layer/CameraDirecting\n");
		return true;
	}

	return false;
}

/*
@fn �X�e�[�W�𐶐�����
*/
void FifthStageCreator::CreateStage()
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
			//CreateCameraDirecting(ix, iy);
		}
	}
}

/*
@fn �v���C���[�𐶐�����
*/
PlayerObject* FifthStageCreator::CreatePlayer()
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
void FifthStageCreator::CreateLayer1(int _indexX, int _indexY)
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

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer1Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn ���C���[2�N���G�C�^�[
@brief  ���C���[2�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer2(int _indexX, int _indexY)
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

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer2SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer2Pos.x, layer2Pos.y + ShiftMoveWallY, layer2Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer2Pos.x, layer2Pos.y, layer2Pos.z - BigMoveWallSize.z));
		break;

	case(SECOND_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer2SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::SECOND_SWITCH);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		new MoveWallBlock(Vector3(layer2Pos.x, layer2Pos.y + ShiftMoveWallY, layer2Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::SECOND_MOVE_WALL, MoveWallSpeed,
			Vector3(layer2Pos.x, layer2Pos.y, layer2Pos.z - BigMoveWallSize.z));
		break;

	case(NORMAL_ENEMY_PARTS):
		// �����Ȃ��G�̐���
		new NormalEnemyObject(layer2Pos, Tag::ENEMY);
		break;

	case(TRACKING_ENEMY_PARTS):
		// �ǐՂ���G�̐���
		new TrackingEnemyObject(layer2Pos, Tag::ENEMY, 600.0f, 1400.0f);
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer2Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(COLLECTION_FIRST):
		// 1�Ԗڂ̎��W���𐶐�
		firstCollectionObject = new CollectionObject(layer2Pos, Tag::COLLECTION, CollectionTag::FIRST);
		break;

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer2Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn ���C���[3�N���G�C�^�[
@brief  ���C���[3�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer3(int _indexX, int _indexY)
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

	case(THIRD_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer3SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer3Pos, BlockSize, Tag::BREAK_GROUND);
		break;

	case(BOMB_PARTS):
		new ExplosionObject(layer3Pos, Tag::BOMB);
		break;
	}
}

/*
@fn ���C���[4�N���G�C�^�[
@brief  ���C���[4�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer4(int _indexX, int _indexY)
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

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer4Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn ���C���[5�N���G�C�^�[
@brief  ���C���[5�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer5(int _indexX, int _indexY)
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

	case(COLLECTION_SECOND):
		// 2�Ԗڂ̎��W���𐶐�
		secondCollectionObject = new CollectionObject(layer5Pos, Tag::COLLECTION, CollectionTag::SECOND);
		break;

	case(THIRD_SWITCH_PARTS):
		// ��O���X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;
	}
}

/*
@fn ���C���[6�N���G�C�^�[
@brief  ���C���[6�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer6(int _indexX, int _indexY)
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
	}
}

/*
@fn ���C���[7�N���G�C�^�[
@brief  ���C���[7�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer7(int _indexX, int _indexY)
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

	case(THIRD_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;
	}
}

/*
@fn ���C���[8�N���G�C�^�[
@brief  ���C���[8�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer8(int _indexX, int _indexY)
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
	}
}

/*
@fn ���C���[9�N���G�C�^�[
@brief  ���C���[9�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer9(int _indexX, int _indexY)
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

	case(THIRD_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(THIRD_MOVE_WALL_PARTS):
		// ��O���̓����ǃI�u�W�F�N�g����
		lastMoveWallBlock = new MoveWallBlock(Vector3(layer9Pos.x, layer9Pos.y + ShiftMoveWallY, layer9Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer9Pos.x, layer9Pos.y, layer9Pos.z - BigMoveWallSize.z));
		break;

	case(ENHANCED_ENEMY_PARTS):
		// �ǐՂ���G�̐���
		new EnhancedEnemyObject(layer9Pos, Tag::ENEMY, 600.0f, 2400.0f);
		break;

	case(CLEAR_OBJECT_PARTS):
		// �X�e�[�W�N���A�I�u�W�F�N�g����
		new NextSceneObject(layer9Pos, Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;
	}
}

/*
@fn ���C���[10�N���G�C�^�[
@brief  ���C���[10�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer10(int _indexX, int _indexY)
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

	case(BOMB_PARTS):
		new ExplosionObject(layer10Pos, Tag::BOMB);
		break;
	}
}

/*
@fn ���C���[11�N���G�C�^�[
@brief  ���C���[11�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer11(int _indexX, int _indexY)
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
	}
}

/*
@fn ���C���[12�N���G�C�^�[
@brief  ���C���[12�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer12(int _indexX, int _indexY)
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
	}
}

/*
@fn ���C���[13�N���G�C�^�[
@brief  ���C���[13�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FifthStageCreator::CreateLayer13(int _indexX, int _indexY)
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
	case(COLLECTION_THIRD):
		// 3�Ԗڂ̎��W���𐶐�
		thirdCollectionObject = new CollectionObject(layer13Pos, Tag::COLLECTION, CollectionTag::THIRD);
		break;

	}
}

void FifthStageCreator::CreateCameraDirecting(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int CameraDirectingData = cameraDirectingData[_indexY][_indexX];
	// ���C���[1�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);
	AABB aabb = { Vector3(-5000.0f,-1800.0f,0.0f),Vector3(2000.0f,1800.0f,4000.0f) };
	AABB aabb2 = { Vector3(-4400.0f,-1800.0f,0.0f),Vector3(1800.0f,1800.0f,4000.0f) };


}
