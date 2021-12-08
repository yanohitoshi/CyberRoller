//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FourthStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FourthStageCreator.h"
#include "ForthStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"
#include "FourthSceneSoundManager.h"

/*
@fn �R���X�g���N�^
@brief  Scene�̐������s��
*/
FourthStageScene::FourthStageScene()
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
	state = SceneState::FOURTH_SATGE_SCENE;

	// �N���G�C�^�[����
	FourthStageCreator* fourthStageCreator = new FourthStageCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!fourthStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = fourthStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		fourthStageCreator->CreateStage();
	}

	// �N���G�C�^�[������W���N���X�̃|�C���^�����炤
	CollectionObject* firstCollection = fourthStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = fourthStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = fourthStageCreator->FindCollectionObject(CollectionTag::THIRD);

	//�V�[��UI��ǉ�
	new ForthStageUI(playerObject, firstCollection, secondCollection, thirdCollection);

	// �N���G�C�^�[�̏�Ԃ�dead�ɂ��ЂÂ���
	fourthStageCreator->SetState(State::Dead);

	// �T�E���h�}�l�[�W���[�N���X�𐶐�
	new FourthSceneSoundManager(this);
}

/*
@fn �f�X�g���N�^
@brief  scene�̍폜���s��
*/
FourthStageScene::~FourthStageScene()
{
}

/*
@fn�@�V�[���̃A�b�v�f�[�g�֐�
@brief	�V�[���̍X�V�������s��
@param	���͏��
@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
*/
SceneState FourthStageScene::Update(const InputState& _inputState)
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
		state = SceneState::FINAL_STAGE_SCENE;
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
		SceneStateChangeAtContinue(SceneState::FOURTH_SATGE_SCENE);
	}

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// �X�V��̃V�[���X�e�[�^�X��Ԃ�
	return state;
}
