#pragma once
#include "StageCreatorBase.h"


class ResultSceneCreator :
    public StageCreatorBase
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  object�̐������s��
	@param	_reUseGameObject �ė��p���邩�ǂ����t���O
	@param	_objectTag �I�u�W�F�N�g���ʗpTag
	*/
	ResultSceneCreator(bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief �}�b�v�f�[�^�̍폜���s��
	*/
	~ResultSceneCreator()override;

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

	/*
	@fn baseLayer�N���G�C�^�[
	@brief  ���C���[1�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateResultMap(int _indexX, int _indexZ);

	/*
	@fn CameraTarget�N���G�C�^�[
	@brief  ���C���[2�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateCamera(int _indexX, int _indexY);

	//�^�C�g���\���p
	std::vector<std::vector<int>> resultMapData;
	std::vector<std::vector<int>> resultCameraData;

	// �}�b�v�f�[�^�̔z��T�C�YX
	int sizeX;
	// �}�b�v�f�[�^�̔z��T�C�YY
	int sizeY;

	// �^�C�g���ł̃v���C���[�����i���o�[
	const int SwitchNumber;
	// �^�C�g���ł̃O���E���h�I�u�W�F�N�g�����i���o�[
	const int CameraNumber;

	// ���U���g�V�[���ł�Object�Ԃ̊Ԋu
	const float ResultOffset;

};

