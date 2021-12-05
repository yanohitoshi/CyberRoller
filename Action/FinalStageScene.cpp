//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FinalStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FinalStageCreator.h"
#include "FinalStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"
#include "FinalSceneSoundManager.h"

/*
@fn �R���X�g���N�^
@brief  Scene�̐������s��
*/
FinalStageScene::FinalStageScene()
	: FinalClearToChangeScene(360)
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
	state = SceneState::FINAL_STAGE_SCENE;

	// �N���G�C�^�[����
	FinalStageCreator* finalStageCreator = new FinalStageCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!finalStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = finalStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		finalStageCreator->CreateStage();
	}

	CollectionObject* firstCollection = finalStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = finalStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = finalStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// �V�[��UI��ǉ�
	new FinalStageUI(playerObject, firstCollection, secondCollection, thirdCollection);

	// �����̖������I�����̂ŃN���G�C�^�[�̏�Ԃ�dead�ɂ��ЂÂ���
	finalStageCreator->SetState(State::Dead);

	new FinalSceneSoundManager(this);
}

/*
@fn �f�X�g���N�^
@brief  scene�̍폜���s��
*/
FinalStageScene::~FinalStageScene()
{
}

/*
@fn�@�V�[���̃A�b�v�f�[�g�֐�
@brief	�V�[���̍X�V�������s��
@param	���͏��
@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
*/
SceneState FinalStageScene::Update(const InputState& _inputState)
{
	// �V�[�����n�܂����烉�C�g����������
	if (startScene == true)
	{
		// �V�[���J�n���̃��C�g�A�b�v����
		StartSceneLightUp();
	}

	isSceneClear = playerObject->GetClearFlag();

	// �ŏI�X�e�[�W�ł̓��C�g�𗎂Ƃ��Ȃ����߃N���A�J�E���g�̂ݐ�����
	if (isSceneClear)
	{
		// �N���A�J�E���g
		++clearCount;
	}

	// �N���A��Ԃ��N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (clearCount >= FinalClearToChangeScene)
	{
		state = SceneState::RESULT_SCENE;
	}

	// �^�C���I�[�o�[��Ԃ����C�g�����܂ŗ��Ƃ���Ԃ�������
	if (CountDownFont::GetTimeOverFlag() && lightDownFlag)
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
		SceneStateChangeAtContinue(SceneState::FINAL_STAGE_SCENE);
	}
	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetRestartFlag())
	{
		state = SceneState::TITLE_SCENE;
	}

	// �V�[���ύX���Ȃ��ꍇ���̃V�[����Ԃ�
	return state;
}