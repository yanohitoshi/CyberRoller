//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ResultSceneCreator.h"
#include "ResultSwitchBaseObject.h"
#include "ResultCameraObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
@param	_reUseGameObject �ė��p���邩�ǂ����t���O
@param	_objectTag �I�u�W�F�N�g���ʗpTag
*/
ResultSceneCreator::ResultSceneCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, SwitchNumber(22)
	, CameraNumber(23)
	, ResultOffset(300.0f)
{
}

/*
@fn �f�X�g���N�^
@brief �}�b�v�f�[�^�̍폜���s��
*/
ResultSceneCreator::~ResultSceneCreator()
{
	//�}�b�v�f�[�^�̍폜
	resultMapData.clear();
	resultCameraData.clear();
}

/*
@fn �t�@�C�����J��
@return �������ۂ�
*/
bool ResultSceneCreator::OpenFile()
{

	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(resultMapData, "Assets/Config/StageData/ResultScene.json", "BaseLayer"))
	{
		printf("do'nt have Layer/BaseLayer\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = resultMapData[0].size();
	sizeY = resultMapData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (CameraTarget)
	if (!readTiledJson(resultCameraData, "Assets/Config/StageData/ResultScene.json", "CameraTarget"))
	{
		printf("do'nt have Layer/CameraTarget\n");
		return true;
	}

	return false;
}

/*
@fn �X�e�[�W�𐶐�����
*/
void ResultSceneCreator::CreateStage()
{
	// ���N���X�Ƀv���C���[�̃|�W�V�����𑗂邽�߂̕ϐ�
	Vector3 sendPlayerPos = Vector3::Zero;

	// �J�����̐���
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// �v���C���[�����֐�
			CreateCamera(ix, iy);
		}
	}

	// �X�e�[�W�f�[�^�����Ă��̏�񂲂Ƃ�class�𐶐�����
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// ���U���gObject�̐���
			CreateResultMap(ix, iy);
		}
	}
}

/*
@fn baseLayer�N���G�C�^�[
@brief  ���C���[1�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ResultSceneCreator::CreateResultMap(int _indexX, int _indexZ)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int BaseLayer = resultMapData[(int)_indexZ][(int)_indexX];
	// ���U���g�X�e�[�W�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 resultBaseLayerPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// �}�b�v�f�[�^�������i���o�[��������
	if (BaseLayer == SwitchNumber)
	{
		// �^�C�g���p�I�u�W�F�N�g�̐���
		new ResultSwitchBaseObject(resultBaseLayerPos, SwitchBaseSize, Tag::RESULT_OBJECT);
	}
}

/*
@fn CameraTarget�N���G�C�^�[
@brief  ���C���[2�̃}�b�v�f�[�^�Ɋ܂܂��I�u�W�F�N�g�̐������s��
@param	_indexX ��������}�b�v�f�[�^�̓Y����X
@param	_indexY ��������}�b�v�f�[�^�̓Y����Y
*/
void ResultSceneCreator::CreateCamera(int _indexX, int _indexZ)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int CameraTarget = resultCameraData[(int)_indexZ][(int)_indexX];
	// �^�C�g���ł̃v���C���[�I�u�W�F�N�g�̃|�W�V����
	Vector3 objectPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// �}�b�v�f�[�^�������i���o�[��������
	if (CameraTarget == CameraNumber)
	{
		new ResultCameraObject(objectPos);
	}
}