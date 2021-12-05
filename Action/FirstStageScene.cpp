//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FirstStageScene.h"
#include "BaseScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FirstStageCreator.h"
#include "FirstStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"
#include "FirstSceneSoundManager.h"

/*
@fn �R���X�g���N�^
@brief  Scene�̐������s��
*/
FirstStageScene::FirstStageScene()
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
	state = SceneState::FIRST_SATGE_SCENE;

	// �N���G�C�^�[����
	FirstStageCreator* secondStageCreator = new FirstStageCreator(false,Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!secondStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = secondStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		secondStageCreator->CreateStage();
	}

	CollectionObject* firstCollection = secondStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = secondStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = secondStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// �V�[��UI��ǉ�
	new FirstStageUI(playerObject,firstCollection,secondCollection,thirdCollection);

	// �N���G�C�^�[�̏�Ԃ�dead�ɂ��ЂÂ���
	secondStageCreator->SetState(State::Dead);

	new FirstSceneSoundManager(this);
}

/*
@fn �f�X�g���N�^
@brief  scene�̍폜���s��
*/
FirstStageScene::~FirstStageScene()
{
}

/*
@fn�@�V�[���̃A�b�v�f�[�g�֐�
@brief	�V�[���̍X�V�������s��
@param	���͏��
@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
*/
SceneState FirstStageScene::Update(const InputState& _inputState)
{
	// �V�[�����n�܂����烉�C�g����������
	if (startScene == true)
	{
		// �V�[���J�n���̃��C�g�A�b�v����
		StartSceneLightUp();
	}

	// �N���A�������̃`�F�b�N�ƃN���A�J�E���g�𐔂��鏈���֐�
	SceneClearCount(playerObject);

	// �N���A��Ԃ��N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (clearCount >= ClearToChangeSceneTime)
	{
		// ���̃V�[���ɕύX
		state = SceneState::SECOND_SATGE_SCENE;
	}

	isTimeOver = CountDownFont::GetTimeOverFlag();

	// �^�C���I�[�o�[��Ԃ����C�g�����܂ŗ��Ƃ���Ԃ�������
	if (isTimeOver && lightDownFlag)
	{
		// �R���e�B�j���[�I������
		ContinueSelect(_inputState);
	}

	// �R���e�j���[���Q�[���I�[�o�[���I�����ꂽ��
	if (isContinueFlag || isEndFlag)
	{
		// �R���e�B�j���[�I�����̃��C�g�J�ڏ���
		LightTransitionAtContinue();
	}

	// �R���e�B�j���[�I����̃V�[���؂�ւ��J�E���g�����ȏ�ɂȂ�����
	if (changeCount >= ContinueToChangeScene)
	{
		// �V�[���X�e�[�^�X�؂�ւ�����
		SceneStateChangeAtContinue(SceneState::FIRST_SATGE_SCENE);
	}

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetRestartFlag())
	{
		state = SceneState::TITLE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}