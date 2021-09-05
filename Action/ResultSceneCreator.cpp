#include "ResultSceneCreator.h"
#include "ResultSwitchBaseObject.h"
#include "ResultCameraObject.h"
/*
   @fn �R���X�g���N�^
   @brief block���m�̊Ԋu�̏�����(offset)
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
 */
ResultSceneCreator::~ResultSceneCreator()
{
	//�}�b�v�f�[�^�̍폜
	resultMapData.clear();
	resultCameraData.clear();
}

bool ResultSceneCreator::OpenFile()
{

	// �X�e�[�W�f�[�^�ǂݍ��� (baseLayer)
	if (!readTiledJson(resultMapData, "Assets/Config/ResultScene.json", "BaseLayer"))
	{
		printf("do'nt have Layer/BaseLayer\n");
		return true;
	}

	// �f�[�^�z��̃T�C�YX��Y��ۑ�
	sizeX = resultMapData[0].size();
	sizeY = resultMapData.size();

	// �X�e�[�W�f�[�^�ǂݍ��� (CameraTarget)
	if (!readTiledJson(resultCameraData, "Assets/Config/ResultScene.json", "CameraTarget"))
	{
		printf("do'nt have Layer/CameraTarget\n");
		return true;
	}

	return false;
}

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

void ResultSceneCreator::CreateResultMap(int _indexX, int _indexZ)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int baseLayer = resultMapData[(int)_indexZ][(int)_indexX];
	// ���U���g�X�e�[�W�̃}�b�v�I�u�W�F�N�g�̃|�W�V����
	Vector3 resultBaseLayerPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// �}�b�v�f�[�^�������i���o�[��������
	if (baseLayer == SwitchNumber)
	{
		// �^�C�g���p�I�u�W�F�N�g�̐���
		new ResultSwitchBaseObject(resultBaseLayerPos, SwitchBaseSize, Tag::RESULT_OBJECT,Tag::RESULT_OBJECT);
	}
}

void ResultSceneCreator::CreateCamera(int _indexX, int _indexZ)
{
	// �X�e�[�W�f�[�^�z�񂩂�}�b�v�f�[�^�����炤
	const unsigned int cameraTarget = resultCameraData[(int)_indexZ][(int)_indexX];
	// �^�C�g���ł̃v���C���[�I�u�W�F�N�g�̃|�W�V����
	Vector3 objectPos = Vector3(0.0f, ResultOffset * _indexX, -ResultOffset * _indexZ);

	// �}�b�v�f�[�^�������i���o�[��������
	if (cameraTarget == CameraNumber)
	{
		new ResultCameraObject(objectPos);
	}
}
