#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"

/*
@file FirstStageCreator.h
@brief FirstStage�𐶐�����
*/
class TutorialStageCreator 
	 : public StageCreatorBase
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  object�̐������s��
	@param	_reUseGameObject �ė��p���邩�ǂ����t���O
	@param	_objectTag �I�u�W�F�N�g���ʗpTag
	*/
	TutorialStageCreator(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn �f�X�g���N�^
	@brief �}�b�v�f�[�^�̍폜���s��
	*/
	~TutorialStageCreator()override;
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

	void CreateCamera();


private:

	/*
	@fn ���C���[1�N���G�C�^�[
	@brief  ���C���[1�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer1(int _indexX, int _indexY);

	/*
	@fn ���C���[2�N���G�C�^�[
	@brief  ���C���[2�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer2(int _indexX, int _indexY);

	/*
	@fn ���C���[3�N���G�C�^�[
	@brief  ���C���[3�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer3(int _indexX, int _indexY);
	
	/*
	@fn ���C���[4�N���G�C�^�[
	@brief  ���C���[4�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer4(int _indexX, int _indexY);

	/*
	@fn ���C���[5�N���G�C�^�[
	@brief  ���C���[5�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer5(int _indexX, int _indexY);

	/*
	@fn �J�������[�h�ύX�|�C���g����
	@brief  �J�������[�h�ύX�|�C���g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateCameraDirecting(int _indexX, int _indexY);

	// ���X�e�[�W�̃��C���[�̍ő�萔
	const int MaxLayerNumber;
	// ���C�g��Z���|�W�V����
	const float LightPointPositionZ;

	//�X�e�[�W�f�[�^
	std::vector<std::vector<int>> cameraDirectingData;
	std::vector<std::vector<int>> layer1StageData;
	std::vector<std::vector<int>> layer2StageData;
	std::vector<std::vector<int>> layer3StageData;
	std::vector<std::vector<int>> layer4StageData;
	std::vector<std::vector<int>> layer5StageData;

	//player�̃f�[�^
	std::vector<std::vector<int>> playerData;

	// �}�b�v�f�[�^�̔z��T�C�YX
	int sizeX;

	// �}�b�v�f�[�^�̔z��T�C�YY
	int sizeY;

};
