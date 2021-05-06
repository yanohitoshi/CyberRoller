#include "ThirdStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "ThirdStageCreator.h"
#include "ThirdStageUI.h"
#include "CountDownFont.h"

ThirdStageScene::ThirdStageScene()
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
	ThirdStageCreator* thirdStageCreator = new ThirdStageCreator(false, Tag::OTHER);

	//�X�e�[�W���t�@�C�����J��
	if (!thirdStageCreator->OpenFile())
	{
		//�v���C���[�̐���
		playerObject = thirdStageCreator->CreatePlayer();
		//�X�e�[�W�𐶐�����
		thirdStageCreator->CreateStage();

	}

	// �V�[��UI��ǉ�
	new ThirdStageUI(playerObject);

}

ThirdStageScene::~ThirdStageScene()
{
}

SceneState ThirdStageScene::Update(const InputState& state)
{
	// �V�[�����n�܂����烉�C�g����������
	if (startScene == true)
	{
		light += CHANGE_LIGHT_SPEED;
		RENDERER->SetAmbientLight(light);
		if (light.x >= MAX_LIGHT)
		{
			startScene = false;
			RENDERER->SetAmbientLight(light);
		}
	}

	// �X�e�[�W�N���A������N���A�J�E���g������ă��C�g�𗎂Ƃ�
	if (playerObject->GetNextSceneFlag() == true)
	{
		++clearCount;
		light -= CHANGE_LIGHT_SPEED;
		RENDERER->SetAmbientLight(light);
	}

	// �N���A��Ԃ��N���A�J�E���g�����𒴂�����V�[����؂�ւ���
	if (playerObject->GetNextSceneFlag() == true && clearCount >= CLEAR_TO_CHANGE_SCENE)
	{
		return SceneState::FINAL_STAGE_SCENE;
	}

	// �^�C���I�[�o�[��Ԃ����C�g�����܂ŗ��Ƃ���Ԃ�������
	if (CountDownFont::timeOverFlag == true && lightDownFlag == true)
	{
		// ���C�g�Œ�
		light = TIMEOVERS_LIGHT;
		RENDERER->SetAmbientLight(light);

		// A�{�^���������ꂽ��
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
		{
			// �R���e�j���[�J�ڏ�Ԃɂ���
			lightDownFlag = false;
			isContinueFlag = true;
		}
		// B�{�^���������ꂽ��
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
		{
			// �Q�[���I�[�o�[��Ԃɂ���
			lightDownFlag = false;
			endFlag = true;
		}
	}

	 // �R���e�j���[���Q�[���I�[�o�[���I�����ꂽ��
	if (isContinueFlag == true || endFlag == true)
	{
		// �J�ڃJ�E���g�J�n
		++changeCount;
		if (changeCount >= CHOICE_CONTINUE_COUNT)
		{
			// �R���e�j���[�������疾�邭�Q�[���I�[�o�[��������Â�����
			if (isContinueFlag == true)
			{
				// ���C�g�A�b�v
				light += CHANGE_LIGHT_SPEED;
				RENDERER->SetAmbientLight(light);
			}
			else if (endFlag == true)
			{
				// ���C�g�_�E��
				light -= CHANGE_LIGHT_SPEED;
				RENDERER->SetAmbientLight(light);
			}
			if (changeCount >= CONTINUE_TO_CHANGE_SCENE)
			{
				// �R���e�j���[��������X�e�[�W�ŏ��փQ�[���I�[�o�[�������烊�U���g��ʂ�
				if (isContinueFlag == true)
				{
					// �R���e�B�j���[���ꂽ�炻�̃X�e�[�W����n�߂邽�߂�
					// �R���e�B�j���[���ꂽ���ǂ������肷�邽�߂̃t���O��؂�ւ���
					Game::SetContinueFlag(true);
					return SceneState::THIRD_SATGE_SCENE;
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
	return SceneState::THIRD_SATGE_SCENE;
}