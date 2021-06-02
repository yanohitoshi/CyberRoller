#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"

/*
@file ThirdStageCreator.h
@brief ThirdStage�𐶐�����
*/
class ThirdStageCreator 
    : public StageCreatorBase
{
public:
	/*
	@fn �R���X�g���N�^
	@brief  object�̐������s��
	@param	_reUseGameObject �ė��p���邩�ǂ����t���O
	@param	_objectTag �I�u�W�F�N�g���ʗpTag
	*/
	ThirdStageCreator(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~ThirdStageCreator()override;

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

	// �����o���̃i���o�[��
	// ���݂̎d�l�ケ���������`�ł����񋓏o���܂���ł����B
	// ���P�Ė͍����ł�
	enum ThirdStagePushBoxNumber
	{
		FRONT_PUSH_BOX = 7,
	};

	// �������̃i���o�[��
	// ���݂̎d�l�ケ���������`�ł����񋓏o���܂���ł����B
	// ���P�Ė͍����ł�
	enum MoveGroundNumber
	{
		// ���C���[4�̃i���o�[��
		THIRD_STAGE_FRONT_MOVE_GROUND = 5,
		THIRD_STAGE_BACK_MOVE_GROUND = 7,
		// ���C���[5�̃i���o�[��
		THIRD_STAGE_LEFT_MOVE_GROUND = 8,
		THIRD_STAGE_RIGHT_MOVE_GROUND = 9,
	};

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
	@fn ���C���[6�N���G�C�^�[
	@brief  ���C���[6�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer6(int _indexX, int _indexY);

	/*
	@fn ���C���[7�N���G�C�^�[
	@brief  ���C���[7�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer7(int _indexX, int _indexY);

	/*
	@fn ���C���[8�N���G�C�^�[
	@brief  ���C���[8�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer8(int _indexX, int _indexY);

	/*
	@fn ���C���[9�N���G�C�^�[
	@brief  ���C���[9�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer9(int _indexX, int _indexY);

	/*
	@fn ���C���[10�N���G�C�^�[
	@brief  ���C���[10�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer10(int _indexX, int _indexY);

	/*
	@fn ���C���[11�N���G�C�^�[
	@brief  ���C���[11�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer11(int _indexX, int _indexY);

	/*
	@fn ���C���[12�N���G�C�^�[
	@brief  ���C���[12�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer12(int _indexX, int _indexY);

	/*
	@fn ���C���[13�N���G�C�^�[
	@brief  ���C���[13�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer13(int _indexX, int _indexY);

	/*
	@fn ���C���[14�N���G�C�^�[
	@brief  ���C���[14�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer14(int _indexX, int _indexY);

	/*
	@fn ���C���[15�N���G�C�^�[
	@brief  ���C���[15�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer15(int _indexX, int _indexY);


	/*
	@fn ���C�g�|�C���g�N���G�C�^�[
	@brief  ���C�g�|�C���g�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLightPoint(int _indexX, int _indexY);

	// ��O�X�e�[�W�̃��C���[�̍ő�萔
	const int MaxLayerNumber;
	// ���C�g��Z���|�W�V����
	const float LightPointPositionZ;
	
	// ��O�X�e�[�W�f�[�^
	std::vector<std::vector<int>> layer1StageData;
	std::vector<std::vector<int>> layer2StageData;
	std::vector<std::vector<int>> layer3StageData;
	std::vector<std::vector<int>> layer4StageData;
	std::vector<std::vector<int>> layer5StageData;
	std::vector<std::vector<int>> layer6StageData;
	std::vector<std::vector<int>> layer7StageData;
	std::vector<std::vector<int>> layer8StageData;
	std::vector<std::vector<int>> layer9StageData;
	std::vector<std::vector<int>> layer10StageData;
	std::vector<std::vector<int>> layer11StageData;
	std::vector<std::vector<int>> layer12StageData;
	std::vector<std::vector<int>> layer13StageData;
	std::vector<std::vector<int>> layer14StageData;
	std::vector<std::vector<int>> layer15StageData;

	std::vector<std::vector<int>> lightPointData;
	//player�̃f�[�^
	std::vector<std::vector<int>> playerData;

	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;

};

