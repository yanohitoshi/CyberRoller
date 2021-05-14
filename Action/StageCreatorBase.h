#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

// �O�u�錾
class PlayerObject;


enum StagePartsName
{
	// �c���ǃp�[�c
	PORTRAIT_WALL_PARTS = 1,
	// �����ǃp�[�c
	LANDSCAPE_WALL_PARTS = 2,
	// ���X�|�[���|�C���g�p�[�c
	RESPOWN_POINT_PARTS = 3,
	// ���p�l���p�[�c
	NEEDLE_PARTS = 16,
	// �X�e�[�W�N���A�I�u�W�F�N�g�p�[�c
	CLEAR_OBJECT_PARTS = 20,
	// �ŏ��̋��X�C�b�`�p�[�c
	FIRST_SWITCH_PARTS = 21,
	// �W�����v�X�C�b�`�p�[�c
	JUMP_SWITCH_PARTS = 40,
	// �ŏ��̋��̓����ǃp�[�c
	FIRST_MOVE_WALL_PARTS = 41,

	// ���C���[���Ƃ̃u���b�N�p�[�c��
	// ��Tiled Map Editor���g�p����JSON�t�@�C���𐧍삷��ۂɃ��C���[�ʂɃu���b�N�̃^�C���}�b�v�̐F��ς��Ă��邽��
	LAYER1_BLOCK_PARTS = 79, // ���C���[1
	LAYER2_BLOCK_PARTS = 78, // ���C���[2
	LAYER3_BLOCK_PARTS = 77, // ���C���[3
	LAYER4_BLOCK_PARTS = 76, // ���C���[4
	LAYER5_BLOCK_PARTS = 75, // ���C���[5
	LAYER6_BLOCK_PARTS = 74, // ���C���[6
	LAYER7_BLOCK_PARTS = 73, // ���C���[7
	LAYER8_BLOCK_PARTS = 72, // ���C���[8
	LAYER9_BLOCK_PARTS = 71, // ���C���[9
	LAYER10_BLOCK_PARTS = 70, // ���C���[10
	LAYER11_BLOCK_PARTS = 69, // ���C���[11
	LAYER12_BLOCK_PARTS = 68, // ���C���[12
	LAYER13_BLOCK_PARTS = 67, // ���C���[13
	LAYER14_BLOCK_PARTS = 66, // ���C���[14
	LAYER15_BLOCK_PARTS = 65, // ���C���[15
	LAYER16_BLOCK_PARTS = 64, // ���C���[16
	LAYER17_BLOCK_PARTS = 63, // ���C���[17


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
	@brief  object�̍폜���s��
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

	// �v���C���[��������class�Ƀv���C���[�̃|�C���^��n�����߂̕ϐ�
	PlayerObject* playerObject;

};

