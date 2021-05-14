#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
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

	/*
	@fn ���C���[1�N���G�C�^�[
	@brief  ���C���[1�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	@param	_playerPos �^�C�g���v���C���[�I�u�W�F�N�g�̃|�W�V����
	*/
	void CreateTitleMap(int _indexX, int _indexY, Vector3 _playerPos);

	/*
	@fn ���C���[2�N���G�C�^�[
	@brief  ���C���[2�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	Vector3 CreatePlayer(int _indexX, int _indexY);

	//�^�C�g���\���p
	std::vector<std::vector<int>> titleMapData;
	std::vector<std::vector<int>> titlePlayerData;

	// �}�b�v�f�[�^�̔z��T�C�YX
	int sizeX;
	// �}�b�v�f�[�^�̔z��T�C�YY
	int sizeY;

	// �^�C�g���ł̃v���C���[�����i���o�[
	const int PlayerNumber;
	// �^�C�g���ł̃O���E���h�I�u�W�F�N�g�����i���o�[
	const int GroundNumber;

	// �z�u����I�u�W�F�N�g�̊Ԋu
	const float Offset;

	// �u���b�N�T�C�Y�萔
	const Vector3 BlockSize;

	// �^�C�g���̃v���C���[�̃|�W�V�����p�ϐ�
	Vector3 playerPos;

};

