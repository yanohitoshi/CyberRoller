#include "FirstStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FirstStageUI.h"
#include "FirstStageCreator.h"


FirstStageScene::FirstStageScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.3f, 0.3f, 0.7f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);

	// �����o�[�ϐ�������
	clearCount = 0;
	startScene = true;

	// �N���G�C�^�[����
	FirstStageCreator* firstStageCreator = new FirstStageCreator(false,Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!firstStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = firstStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		firstStageCreator->CreateStage();
	}

	// �V�[��UI��ǉ�
	new FirstStageUI();
}

FirstStageScene::~FirstStageScene()
{
}

SceneState FirstStageScene::Update(const InputState& _inputState)
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
		return SceneState::SECOND_SATGE_SCENE;
	}

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	// �V�[���ύX���Ȃ��ꍇ���̃V�[����Ԃ�
	return SceneState::FIRST_SATGE_SCENE;
}