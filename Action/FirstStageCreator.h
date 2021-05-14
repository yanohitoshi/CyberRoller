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

	//�t�@�[�X�g�X�e�[�W�f�[�^
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

	//�z�u����I�u�W�F�N�g�̊Ԋu�B�T�C�Y
	const float Offset;

	// �����ǂ̃|�W�V�������������炷�萔
	// Y���͒��S�̂��炷���߁EZ���͏������܂�����ԂŐ�������������
	const float ShiftMoveWallY;
	const float ShiftMoveWallZ;

	// �����ǂ̑��x�萔
	const float MoveWallSpeed;

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
	// �����ǃI�u�W�F�N�g�̃T�C�Y�萔
	const Vector3 MoveWallSize;

	// ���X�|�[���|�C���g�I�u�W�F�N�g�̓����蔻��T�C�Y�iAABB�j�萔
	const AABB RespawnBox;

};

