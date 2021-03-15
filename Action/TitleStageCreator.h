#pragma once
#include "StageCreatorBase.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file TitleStageCreator.h
@brief TitleStage�𐶐�����
*/
class TitleStageCreator :
    public StageCreatorBase
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  object�̐������s��
	@param	_reUseGameObject �ė��p���邩�ǂ����t���O
	@param	_objectTag �I�u�W�F�N�g���ʗpTag
	*/
	TitleStageCreator(bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~TitleStageCreator()override;

	/*
	@fn �t�@�C�����J��
	@return �������ۂ�
	*/
	bool OpenFile();

	/*
	@fn �X�e�[�W�𐶐�����
	*/
	void CreateStage();

private:

	//�^�C�g���\���p
	std::vector<std::vector<int>> titleMapData;
	std::vector<std::vector<int>> titlePlayerData;

	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;
	//�z�u����I�u�W�F�N�g�̊Ԋu�B�T�C�Y
	float offset;

};

