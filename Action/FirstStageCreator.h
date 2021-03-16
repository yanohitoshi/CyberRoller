#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file FirstStageCreator.h
@brief FirstStage�𐶐�����
*/
class FirstStageCreator 
	 : public StageCreatorBase
{
public:
	/*
	@fn �R���X�g���N�^
	@brief  object�̐������s��
	@param	_reUseGameObject �ė��p���邩�ǂ����t���O
	@param	_objectTag �I�u�W�F�N�g���ʗpTag
	*/
	FirstStageCreator(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~FirstStageCreator()override;
	/*
	@fn �t�@�C�����J��
	@return �������ۂ�
	*/
	bool OpenFile();

	/*
	@fn �v���C���[�𐶐�����
	*/
	class PlayerObject* CreatePlayer();

	/*
	@fn �X�e�[�W�𐶐�����
	*/
	void CreateStage();

private:

	//�t�@�[�X�g�X�e�[�W�f�[�^
	std::vector<std::vector<int>> layer1StageData;
	std::vector<std::vector<int>> layer2StageData;
	std::vector<std::vector<int>> layer3StageData;
	std::vector<std::vector<int>> layer4StageData;
	std::vector<std::vector<int>> layer5StageData;

	//player�̃f�[�^
	std::vector<std::vector<int>> playerData;

	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;
	//�z�u����I�u�W�F�N�g�̊Ԋu�B�T�C�Y
	float offset;

};

