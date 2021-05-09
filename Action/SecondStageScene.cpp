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
	dir.direction = Vector3(0.0f, 0.0f, 1.0f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �����o�[�ϐ�������
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	isContinueFlag = false;
	endFlag = false;
	lightDownFlag = true;

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

SceneState SecondStageScene::Update(const InputState& state)
{
	// �V�[�����n�܂����烉�C�g����������
	if (startScene == true)
	{
		light += ChangeLightSpeed;
		RENDERER->SetAmbientLight(light);
		if (light.x >= MaxLight)
		{
			startScene = false;
			RENDERER->SetAmbientLight(light);
		}
	}

	// �X�e�[�W�N���A������N���A�J�E���g������ă��C�g�𗎂Ƃ�
	if (playerObject->GetNextSceneFlag() == true)
	{
		++clearCount;
		light -= ChangeLightSpeed;
		RENDERER->SetAmbientLight(light);
	}

	// �N���A��Ԃ��N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (clearCount >= ClearToChangeScene)
	{
		return SceneState::THIRD_SATGE_SCENE;
	}

	// �^�C���I�[�o�[��Ԃ����C�g�����܂ŗ��Ƃ���Ԃ�������
	if (CountDownFont::timeOverFlag == true && lightDownFlag == true)
	{
		// ���C�g�Œ�
		light = TimeoversLight;
		RENDERER->SetAmbientLight(light);

		// A�{�^���������ꂽ��
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
		{
			lightDownFlag = false;
			// �R���e�j���[�J�ڏ�Ԃɂ���
			isContinueFlag = true;
		}

		// B�{�^���������ꂽ��
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
		{
			lightDownFlag = false;
			// �Q�[���I�[�o�[��Ԃɂ���
			endFlag = true;
		}
	}

	// �R���e�j���[���Q�[���I�[�o�[���I�����ꂽ��
	if (isContinueFlag == true || endFlag == true)
	{
		// �J�ڃJ�E���g�J�n
		++changeCount;
		if (changeCount >= ChoiceContinueCount)
		{
			// �R���e�j���[�������疾�邭�Q�[���I�[�o�[��������Â�����
			if (isContinueFlag == true)
			{
				// ���C�g�A�b�v
				light += ChangeLightSpeed;
				RENDERER->SetAmbientLight(light);
			}
			else if (endFlag == true)
			{
				// ���C�g�_�E��
				light -= ChangeLightSpeed;
				RENDERER->SetAmbientLight(light);
			}
			if (changeCount >= ContinueToChangeScene)
			{
				// �R���e�j���[��������X�e�[�W�ŏ��փQ�[���I�[�o�[�������烊�U���g��ʂ�
				if (isContinueFlag == true)
				{
					// �R���e�B�j���[���ꂽ�炻�̃X�e�[�W����n�߂邽�߂�
					// �R���e�B�j���[���ꂽ���ǂ������肷�邽�߂̃t���O��؂�ւ���
					Game::SetContinueFlag(true);
					return SceneState::SECOND_SATGE_SCENE;
				}
				else if (endFlag == true)
				{
					return SceneState::RESULT_SCENE;
				}
			}
		}
	}

	// ��莞�ԑ��삪�Ȃ�������^�C�g����
	if (playerObject->GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	// �V�[���ύX���Ȃ��ꍇ���̃V�[����Ԃ�
	return SceneState::SECOND_SATGE_SCENE;
}