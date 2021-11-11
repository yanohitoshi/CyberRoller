#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>
#include <unordered_map>
#include "MoveBlockObject.h"
#include "EnemyObjectBase.h"
#include "PushBoxObject.h"

// �O�u�錾
class PlayerObject;
class MoveWallBlock;
class CollectionObject;
enum class CollectionTag;

/*
@enum�@�X�e�[�W�𐶐�����ɓ������Ďg�p����p�[�c�̖��O
*/
enum StagePartsName
{
	// ����u���b�N�p�[�c
	BREAK_BLOCK_PARTS = 59,

	// �������p�[�c
	BOMB_PARTS = 60,

	// �E�񂹂̃p���[�Z�����C�g�p�[�c
	POWERCELLS_LIGHT_PARTS_RIGHT = 1,
	// ���񂹂̃p���[�Z�����C�g�p�[�c
	POWERCELLS_LIGHT_PARTS_LEFT = 2,

	// ���X�|�[���|�C���g�p�[�c
	RESPOWN_POINT_PARTS = 18,

	// ���p�l���p�[�c
	NEEDLE_PARTS = 6,

	// �X�e�[�W�N���A�I�u�W�F�N�g�p�[�c
	CLEAR_OBJECT_PARTS = 20,

	// �����̃X�C�b�`�p�[�c
	FIRST_SWITCH_PARTS = 21,
	// �����̃X�C�b�`�p�[�c
	SECOND_SWITCH_PARTS = 22,
	// ��O���̃X�C�b�`�p�[�c
	THIRD_SWITCH_PARTS = 23,
	
	// �ŏ��E�ɓ���block�p�[�c
	RIGHT_MOVE_BLOCK_PARTS = 24,
	// �ŏ����ɓ���block�p�[�c
	LEFT_MOVE_BLOCK_PARTS = 25,

	// �W�����v�X�C�b�`�p�[�c
	JUMP_SWITCH_PARTS = 7,

	// �����̓����ǃp�[�c
	FIRST_MOVE_WALL_PARTS = 41,
	// �����̓����ǃp�[�c
	SECOND_MOVE_WALL_PARTS = 42,
	// ��O���̓����ǃp�[�c
	THIRD_MOVE_WALL_PARTS = 43,

	// �����Ȃ��G
	NORMAL_ENEMY_PARTS = 44,
	// �ŏ��E�����Ɉړ�����G
	RIGHT_MOVE_ENEMY_PARTS = 45,
	// �ŏ��������Ɉړ�����G
	LEFT_MOVE_ENEMY_PARTS = 46,
	// �ǐՂ���G
	TRACKING_ENEMY_PARTS = 47,

	// 1�Ԗڂ̎��W���p�[�c
	COLLECTION_FIRST = 3,
	// 2�Ԗڂ̎��W���p�[�c
	COLLECTION_SECOND = 4,
	// 3�Ԗڂ̎��W���p�[�c
	COLLECTION_THIRD = 5,

	// �v���C���[
	PLAYER_PARTS = 19,

	// ���C���[���Ƃ̃u���b�N�p�[�c��
	// ��Tiled Map Editor���g�p����JSON�t�@�C���𐧍삷��ۂɃ��C���[�ʂɃu���b�N�̃^�C���}�b�v�̐F��ς��Ă��邽��
	LAYER1_BLOCK_PARTS = 61, // ���C���[1
	LAYER2_BLOCK_PARTS = 62, // ���C���[2
	LAYER3_BLOCK_PARTS = 63, // ���C���[3
	LAYER4_BLOCK_PARTS = 64, // ���C���[4
	LAYER5_BLOCK_PARTS = 65, // ���C���[5
	LAYER6_BLOCK_PARTS = 66, // ���C���[6
	LAYER7_BLOCK_PARTS = 67, // ���C���[7
	LAYER8_BLOCK_PARTS = 68, // ���C���[8
	LAYER9_BLOCK_PARTS = 69, // ���C���[9
	LAYER10_BLOCK_PARTS = 70, // ���C���[10
	LAYER11_BLOCK_PARTS = 71, // ���C���[11
	LAYER12_BLOCK_PARTS = 72, // ���C���[12
	LAYER13_BLOCK_PARTS = 73, // ���C���[13
	LAYER14_BLOCK_PARTS = 74, // ���C���[14
	LAYER15_BLOCK_PARTS = 75, // ���C���[15
	LAYER16_BLOCK_PARTS = 76, // ���C���[16
	LAYER17_BLOCK_PARTS = 77, // ���C���[17
};

/*
@file StageCreatorBase.h
@brief �X�e�[�W����class�̊��N���X
*/
class StageCreatorBase :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  object�̐������s��
	@param	_reUseGameObject �ė��p���邩�ǂ����t���O
	@param	_objectTag �I�u�W�F�N�g���ʗpTag
	*/
	StageCreatorBase(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn �f�X�g���N�^
	@brief  �}�b�v�f�[�^�̍폜���s��
	*/
	~StageCreatorBase()override;


protected:

	/*
	@fn Json�t�@�C����ǂݍ��݃R���e�i�^�Ɋi�[����
	@param _mapDate �i�[���������R���e�i�ւ̃A�h���X
	@param _fileName Json�t�@�C���A�h���X
	@param _layerName Json�t�@�C�����̃��C���[�A�h���X
	@return false=���s
	*/
	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _filename, const char* _layerName);
	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName);

	/*
	@fn �v���C���[�𐶎Y����֐�
	@brief  �v���C���[�p�}�b�v�f�[�^��p���ăv���C���[�𐶎Y����
	@param	_data �}�b�v�f�[�^
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void ProductionPlayer(int _data, int _indexX, int _indexY);

	/*
	@fn �������̃f�[�^�\���̂𐶐�����֐�
	@param  �ǂꂭ�炢�̋��������̂�
	@param�@�ǂ̕����ɓ����̂�
	@param�@���x
	@param�@�ǂ̕����ɓ����̂����ʂ��邽�߂̃^�O
	*/
	void SetMoveBlockData(const float _distance, const Vector3 _direction, const float _speed,const Vector3 _objectSize,MoveDirectionTag _moveTag);
	

	// �������N���X�Ƀf�[�^��n�����߂̕ϐ�
	MoveBlockData moveBlockData;

	/*
	@fn �v�b�V���{�[�h�̃f�[�^�\���̂𐶐�����֐�
	@param  �ǂꂭ�炢�̋��������̂�
	@param�@�ǂ̕����ɓ����̂�
	@param�@���x
	@param�@�ǂ̕����ɓ����̂����ʂ��邽�߂̃^�O
	*/
	void SetPushBoxData(const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed, MoveDirectionTag _moveTag);

	// �v�b�V���{�[�h���N���X�Ƀf�[�^��n�����߂̕ϐ�
	PushBoxData pushBoxData;

	/*
	@fn �����G�̃f�[�^�\���̂𐶐�����֐�
	@param�@���x
	@param�@�ǂ̕����ɓ����̂�
	@param  �ǂꂭ�炢�̋��������̂�
	@param�@�ǂ̕����ɓ����̂����ʂ��邽�߂̃^�O
	*/
	void SetMoveEnemyData(const float _speed, const Vector3 _direction, const float _distance, MoveEnemyTag _moveTag);
	
	// �����G�N���X�Ƀf�[�^��n�����߂̕ϐ�
	MoveEnemyData moveEnemyData;

	// �v���C���[��������class�Ƀv���C���[�̃|�C���^��n�����߂̕ϐ�
	PlayerObject* playerObject;

	// ���̃V�[���ł̍Ō�̓����ǂ̃|�C���^
	// �N���A�I�u�W�F�N�g�ɓn��(�G�t�F�N�g�𔭐�������g���K�[�Ɏg�p���邽��)
	MoveWallBlock* lastMoveWallBlock;


	CollectionObject* firstCollectionObject;
	CollectionObject* secondCollectionObject;
	CollectionObject* thirdCollectionObject;

	// �����ǂ̃|�W�V�������������炷�萔
	// Y���͒��S�̂��炷���߁EZ���͏������܂�����ԂŐ�������������
	const float ShiftMoveWallY;
	const float ShiftMoveWallZ;

	// �����ǂ̑��x�萔
	const float MoveWallSpeed;

	//X�EY���̃I�u�W�F�N�g�̊Ԋu�B
	const float Offset;
	// Z���̃I�u�W�F�N�g�̊Ԋu
	const float OffsetZ;

	// �v���C���[�̐��������Ƃ���Z���̃|�W�V�����萔
	const float PlayerPositionZ;

	// �u���b�N�I�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 BlockSize;

	// �X�C�b�`�I�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 SwitchBaseSize;

	// �W�����v�X�C�b�`�I�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 JumpSwitchSize;

	// �j�[�h���I�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 NeedlePanelSize;

	// �c���ǃI�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 PortraitWallBlockSize;

	// �����ǃI�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 LandscapeWallBlockSize;

	// �傫�������ǃI�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 BigMoveWallSize;

	// �����������ǃI�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 SmallMoveWallSize;

	// 
	const Vector3 LightObjectSize;

	// ���X�|�[���|�C���g�I�u�W�F�N�g�̓����蔻��T�C�Y�iAABB�j�萔
	const AABB RespawnBox;

	// ���X�|�[���|�C���g�I�u�W�F�N�g�̓����蔻��T�C�Y�iAABB�j�萔
	const AABB LightPointBox;

	// �X�C�b�`�̃|�W�V�����͑��̃I�u�W�F�N�g�ƈႢ���炷�K�v������̂�
	// ���̂��߂ɗp����萔
	const float ShiftSwitchPositionZ;

	// ���C���[���̍ő�l
	const int MaxLayer;

	// ���C���[���ƂɊ��蓖�Ă�I�u�W�F�N�g��Z���̒l���i�[����z��
	float objectPositionZ[18];

public:

	CollectionObject* FindCollectionObject(CollectionTag _CollectionTag);

};

