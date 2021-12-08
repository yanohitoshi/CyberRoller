#include "ThirdStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "ThirdStageCreator.h"
#include "ThirdStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"
#include "ThirdSceneSoundManager.h"

ThirdStageScene::ThirdStageScene()
{
	// ���C�g��񏉊���
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �����o�[�ϐ�������
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	isContinueFlag = false;
	isEndFlag = false;
	lightDownFlag = true;
	state = SceneState::THIRD_SATGE_SCENE;

	// �N���G�C�^�[����
	ThirdStageCreator* thirdStageCreator = new ThirdStageCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!thirdStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = thirdStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		thirdStageCreator->CreateStage();
	}

	// �N���G�C�^�[������W���N���X�̃|�C���^�����炤
	CollectionObject* firstCollection = thirdStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = thirdStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = thirdStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// �V�[��UI��ǉ�
	new ThirdStageUI(playerObject, firstCollection, secondCollection, thirdCollection);

	// �N���G�C�^�[�̏�Ԃ�dead�ɂ��ЂÂ���
	thirdStageCreator->SetState(State::Dead);

	// �T�E���h�}�l�[�W���[�N���X�𐶐�
	new ThirdSceneSoundManager(this);
}

ThirdStageScene::~ThirdStageScene()
{
}

SceneState ThirdStageScene::Update(const InputState& _inputState)
{
	// �V�[�����n�܂����烉�C�g����������
	if (startScene == true)
	{
		// �V�[���J�n���̃��C�g�A�b�v����
		StartSceneLightUp();
	}

	// �N���A�������̃`�F�b�N�ƃN���A�J�E���g�𐔂��鏈���֐�
	SceneClearCount(playerObject);

	// �N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (clearCount >= ClearToChangeSceneTime)
	{
		state = SceneState::FOURTH_SATGE_SCENE;
	}

	// �^�C���I�[�o�[��Ԃ����C�g�����܂ŗ��Ƃ���Ԃ�������
	if (CountDownFont::GetTimeOverFlag() == true && lightDownFlag == true)
	{
		// �R���e�B�j���[�I������
		ContinueSelect(_inputState);
	}

	// �R���e�j���[���Q�[���I�[�o�[���I�����ꂽ��
	if (isContinueFlag == true || isEndFlag == true)
	{
		// �R���e�B�j���[�I�����̃��C�g�J�ڏ���
		LightTransitionAtContinue();
	}

	// �R���e�B�j���[�I����̃V�[���؂�ւ��J�E���g�����ȏ�ɂȂ�����
	if (changeCount >= ContinueToChangeScene)
	{
		// �V�[���X�e�[�^�X�؂�ւ�����
		SceneStateChangeAtContinue(SceneState::THIRD_SATGE_SCENE);
	}

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}
