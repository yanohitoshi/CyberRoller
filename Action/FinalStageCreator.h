#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageCreatorBase.h"

/*
@file FinalStageCreator.h
@brief FinalStage�𐶐�����
*/
class FinalStageCreator :
    public StageCreatorBase
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  object�̐������s��
	@param	_reUseGameObject �ė��p���邩�ǂ����t���O
	@param	_objectTag �I�u�W�F�N�g���ʗpTag
	*/
	FinalStageCreator(bool _reUseGameObject, const Tag _objectTag);
	
	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~FinalStageCreator()override;
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
	enum FinalStagePushBoxNumber
	{
		// �������̉����o���̗񋓃i���o�[
		LEFT_PUSH_BOX_NUMBER_1 = 46,
		LEFT_PUSH_BOX_NUMBER_2 = 47,
		LEFT_PUSH_BOX_NUMBER_3 = 48,
		LEFT_PUSH_BOX_NUMBER_4 = 49,
		LEFT_PUSH_BOX_NUMBER_5 = 44,

		// �E�����̉����o���̗񋓃i���o�[
		RIGHT_PUSH_BOX_NUMBER_1 = 50,
		RIGHT_PUSH_BOX_NUMBER_2 = 51,
		RIGHT_PUSH_BOX_NUMBER_3 = 52,
		RIGHT_PUSH_BOX_NUMBER_4 = 53,
		RIGHT_PUSH_BOX_NUMBER_5 = 45,

	};

	// �������̃i���o�[��
	// ���݂̎d�l�ケ���������`�ł����񋓏o���܂���ł����B
	// ���P�Ė͍����ł�
	enum FinalStageMoveGroundNumber
	{
		// �ŏ��̈ړ��������O�ړ��̓����n�ʂ̗񋓃i���o�[
		FRONT_MOVE_GROUND_NUMBER_1 = 5,
		FRONT_MOVE_GROUND_NUMBER_3 = 9,

		// �ŏ��̈ړ����������ړ��̓����n�ʂ̗񋓃i���o�[
		BACK_MOVE_GROUND_NUMBER_1 = 6,
		BACK_MOVE_GROUND_NUMBER_2 = 10,

		// �ŏ��̈ړ����������ړ��̓����n�ʂ̗񋓃i���o�[
		LEFT_MOVE_GROUND_NUMBER_1 = 11,
		LEFT_MOVE_GROUND_NUMBER_2 = 12,
		LEFT_MOVE_GROUND_NUMBER_3 = 7,

		// �ŏ��̈ړ��������E�ړ��̓����n�ʂ̗񋓃i���o�[
		RIGHT_MOVE_GROUND_NUMBER_1 = 13,
		RIGHT_MOVE_GROUND_NUMBER_2 = 8,

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
	@fn ���C���[16�N���G�C�^�[
	@brief  ���C���[16�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer16(int _indexX, int _indexY);

	/*
	@fn ���C���[17�N���G�C�^�[
	@brief  ���C���[17�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLayer17(int _indexX, int _indexY);

	/*
	@fn ���C�g�|�C���g�N���G�C�^�[
	@brief  ���C�g�|�C���g�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
	@param	_indexX ��������}�b�v�f�[�^�̓Y����X
	@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
	*/
	void CreateLightPoint(int _indexX, int _indexY);

	// �ŏI�X�e�[�W�̃��C���[�̍ő�萔
	const int MaxLayerNumber;

	// ���C�g��Z���|�W�V����
	const float LightPointPositionZ;
	
	// �ŏI�X�e�[�W�f�[�^
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
	std::vector<std::vector<int>> layer16StageData;
	std::vector<std::vector<int>> layer17StageData;

	std::vector<std::vector<int>> lightPointData;
	//player�̃f�[�^
	std::vector<std::vector<int>> playerData;

	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;
	
};

