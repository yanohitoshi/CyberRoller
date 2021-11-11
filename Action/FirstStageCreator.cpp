//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FirstStageCreator.h"
#include "AutoMoveCamera.h"
#include "CameraChangePoint.h"
#include "PlayerObject.h"
#include "GroundObject.h"
#include "BreakBlockObject.h"
#include "MoveWallBlock.h"
#include "LightObject.h"
#include "SwitchBaseObject.h"
#include "JumpSwitchObject.h"
#include "NeedlePanelObject.h"
#include "NextSceneObject.h"
#include "RespawnPoint.h"
#include "NormalEnemyObject.h"
#include "MoveEnemyObject.h"
#include "ExplosionObject.h"
#include "CollectionObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_reUseGameObject �ė��p���邩�ǂ����t���O
@param	_objectTag �I�u�W�F�N�g���ʗpTag
*/
FirstStageCreator::FirstStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(5)
	, LightPointPositionZ(3000.0f)
{
}

/*
@fn �f�X�g���N�^
@brief �}�b�v�f�[�^�̍폜���s��
*/
FirstStageCreator::~FirstStageCreator()
{
	//�}�b�v�f�[�^�̌�n��
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	cameraDirectingData.clear();
	playerData.clear();
}

/*
@fn �t�@�C�����J��
@return �������ۂ�
*/
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

	// �X�e�[�W�f�[�^�ǂݍ��� (CameraDirecting)
	if (!readTiledJson(cameraDirectingData, "Assets/Config/firstStageMap.json", "CameraDirecting"))
	{
		printf("do'nt have Layer/CameraDirecting\n");
		return true;
	}

	return false;
}

/*
@fn �X�e�[�W�𐶐�����
*/
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

void FirstStageCreator::CreateCamera()
{
}

/*
@fn �v���C���[�𐶐�����
*/
PlayerObject* FirstStageCreator::CreatePlayer()
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
void FirstStageCreator::CreateLayer1(int _indexX, int _indexY)
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
void FirstStageCreator::CreateLayer2(int _indexX, int _indexY)
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
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND,true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(JUMP_SWITCH_PARTS):
		// �W�����v�X�C�b�`�I�u�W�F�N�g����
		new JumpSwitchObject(layer2SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// ��[�h���I�u�W�F�N�g����
		new NeedlePanelObject(layer2SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer2Pos, BlockSize,Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn ���C���[3�N���G�C�^�[
@brief  ���C���[3�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FirstStageCreator::CreateLayer3(int _indexX, int _indexY)
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

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer3Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer3Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(NORMAL_ENEMY_PARTS):
		// �����Ȃ��G�𐶐�
		new NormalEnemyObject(layer3Pos, Tag::ENEMY, playerObject);
		break;

	case(BOMB_PARTS):
		new ExplosionObject(layer3Pos, Tag::BOMB);
		break;

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer3Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn ���C���[4�N���G�C�^�[
@brief  ���C���[4�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void FirstStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int Layer4 = layer4StageData[_indexY][_indexX];
	// ���C���[4�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3]);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (Layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// �u���b�N�I�u�W�F�N�g����
		new GroundObject(layer4Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer4Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer4Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer4Pos, RespawnBox, Tag::RESPOWN_POINT);
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
void FirstStageCreator::CreateLayer5(int _indexX, int _indexY)
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
	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// �p���[�Z�����C�g�̐���
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// �����̓����ǃI�u�W�F�N�g����
		lastMoveWallBlock = new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + ShiftMoveWallY, layer5Pos.z - ShiftMoveWallZ), SmallMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - SmallMoveWallSize.z));
		break;

	case(FIRST_SWITCH_PARTS):
		// �����X�C�b�`�I�u�W�F�N�g����
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH,true);
		break;

	case(CLEAR_OBJECT_PARTS):
		// �X�e�[�W�N���A�I�u�W�F�N�g����
		new NextSceneObject(Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z), Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;

	case(RESPOWN_POINT_PARTS):
		// ���X�|�[���|�C���g�I�u�W�F�N�g����
		new RespawnPoint(layer5Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(NORMAL_ENEMY_PARTS):
		// �����Ȃ��G�𐶐�
		new NormalEnemyObject(layer5Pos, Tag::ENEMY, playerObject);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// ���E�ɓ����G�ŗL�̃f�[�^�\���̂��Z�b�g
		SetMoveEnemyData(100.0f, Vector3::UnitY, 400.0f, MoveEnemyTag::RIGHT_MOVE);
		// ���E�ɓ����G�𐶐�
		new MoveEnemyObject(layer5Pos, Tag::ENEMY, playerObject, moveEnemyData);
		break;

	case(BREAK_BLOCK_PARTS):
		new BreakBlockObject(layer5Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

void FirstStageCreator::CreateCameraDirecting(int _indexX, int _indexY)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int CameraDirectingData = cameraDirectingData[_indexY][_indexX];
	// ���C���[1�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 cameraPos = Vector3(Offset * _indexX, -Offset * _indexY, 3000.0f);

	// �}�b�v�f�[�^�����Ă��ꂼ��̃I�u�W�F�N�g�𐶐�
	switch (CameraDirectingData)
	{
	case(17):
		// ���C���J���������Ɠ����Ƀv���C���[�I�u�W�F�N�g�̃|�C���^��n��
		GameObject::CreateMainCamera(cameraPos, playerObject);
		break;
	}
}
