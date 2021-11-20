//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SecondStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "SecondStageCreator.h"
#include "SecondStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"

/*
@fn �R���X�g���N�^
@brief  Scene�̐������s��
*/
SecondStageScene::SecondStageScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �����o�[�ϐ�������
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	isContinueFlag = false;
	endFlag = false;
	lightDownFlag = true;
	state = SceneState::SECOND_SATGE_SCENE;

	// �N���G�C�^�[����
	SecondStageCreator* thirdStageCreator = new SecondStageCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!thirdStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = thirdStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		thirdStageCreator->CreateStage();
	}

	CollectionObject* firstCollection = thirdStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = thirdStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = thirdStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// �V�[��UI��ǉ�
	new SecondStageUI(playerObject, firstCollection, secondCollection, thirdCollection);
}

/*
@fn �f�X�g���N�^
@brief  scene�̍폜���s��
*/
SecondStageScene::~SecondStageScene()
{
}

/*
@fn�@�V�[���̃A�b�v�f�[�g�֐�
@brief	�V�[���̍X�V�������s��
@param	���͏��
@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
*/
SceneState SecondStageScene::Update(const InputState& _inputState)
{
	// �V�[�����n�܂����烉�C�g����������
	if (startScene == true)
	{
		// �V�[���J�n���̃��C�g�A�b�v����
		StartSceneLightUpProcess();
	}

	// �N���A�������̃`�F�b�N�ƃN���A�J�E���g�𐔂��鏈���֐�
	SceneClearCountProcess(playerObject);

	// �N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (clearCount >= ClearToChangeSceneTime)
	{
		state = SceneState::THIRD_SATGE_SCENE;
	}

	// �^�C���I�[�o�[��Ԃ����C�g�����܂ŗ��Ƃ���Ԃ�������
	if (CountDownFont::GetTimeOverFlag() == true && lightDownFlag == true)
	{
		// �R���e�B�j���[�I������
		ContinueSelectProcess(_inputState);
	}

	 // �R���e�j���[���Q�[���I�[�o�[���I�����ꂽ��
	if (isContinueFlag == true || endFlag == true)
	{
		// �R���e�B�j���[�I�����̃��C�g�J�ڏ���
		LightTransitionAtContinue();
	}

	// �R���e�B�j���[�I����̃V�[���؂�ւ��J�E���g�����ȏ�ɂȂ�����
	if (changeCount >= ContinueToChangeScene)
	{
		// �V�[���X�e�[�^�X�؂�ւ�����
		SceneStateChangeAtContinue(SceneState::SECOND_SATGE_SCENE);
	}

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}