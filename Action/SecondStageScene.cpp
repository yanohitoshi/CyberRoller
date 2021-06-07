#include "SecondStageScene.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "SecondStageCreator.h"
#include "SecondStageUI.h"
#include "CountDownFont.h"

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
	SecondStageCreator* secondStageCreator = new SecondStageCreator(false,Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!secondStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = secondStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		secondStageCreator->CreateStage();
	}

	// �V�[��UI��ǉ�
	new SecondStageUI(playerObject);

}

SecondStageScene::~SecondStageScene()
{
}

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

	// �N���A��Ԃ��N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (clearCount >= ClearToChangeSceneTime)
	{
		// ���̃V�[���ɕύX
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
	if (playerObject->GetReStartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}