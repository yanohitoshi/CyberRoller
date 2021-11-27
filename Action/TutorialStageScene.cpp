//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TutorialStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "TutorialStageUI.h"
#include "TutorialStageCreator.h"

/*
@fn �R���X�g���N�^
@brief  Scene�̐������s��
*/
TutorialStageScene::TutorialStageScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);

	// �����o�[�ϐ�������
	clearCount = 0;
	startScene = true;

	// �N���G�C�^�[����
	TutorialStageCreator* tutorialStageCreator = new TutorialStageCreator(false,Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!tutorialStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = tutorialStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		tutorialStageCreator->CreateStage();
	}

	// �V�[��UI��ǉ�
	new TutorialStageUI();
}

/*
@fn �f�X�g���N�^
@brief  scene�̍폜���s��
*/
TutorialStageScene::~TutorialStageScene()
{
}

/*
@fn�@�V�[���̃A�b�v�f�[�g�֐�
@brief	�V�[���̍X�V�������s��
@param	���͏��
@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
*/
SceneState TutorialStageScene::Update(const InputState& _inputState)
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
		return SceneState::STAGE_SELECT_SCENE;
	}

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetRestartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	// �V�[���ύX���Ȃ��ꍇ���̃V�[����Ԃ�
	return SceneState::TUTORIAL_SATGE_SCENE;
}