#include "BaseScene.h"
#include "Renderer.h"
#include "PlayerObject.h"

void BaseScene::StartSceneLightUpProcess()
{
	// ���C�g�̐��l�𖾂邭����
	light += ChangeLightSpeed;
	// �����_���[�ɒl���Z�b�g
	RENDERER->SetAmbientLight(light);

	// ���C�g�̐��l�����ȏ�ɂȂ�����
	if (light.x >= MaxLight)
	{
		// �V�[���J�n�t���O��false�ɕύX
		startScene = false;
		// �ŏI�̒l���Z�b�g
		RENDERER->SetAmbientLight(light);
	}
}

void BaseScene::SceneClearCountProcess(PlayerObject* _playerObject)
{
	if (_playerObject->GetClearFlag() == true)
	{
		++clearCount;
		light -= ChangeLightSpeed;
		RENDERER->SetAmbientLight(light);
	}
}

void BaseScene::ContinueSelectProcess(const InputState& state)
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

void BaseScene::LightTransitionAtContinue()
{
	// �J�ڃJ�E���g�J�n
	++changeCount;

	// �R���e�B�j���[�I�����
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

	}
}

void BaseScene::SceneStateChangeAtContinue(SceneState _nowScene)
{
	// �R���e�j���[��������X�e�[�W�ŏ��փQ�[���I�[�o�[�������烊�U���g��ʂ�
	if (isContinueFlag == true)
	{
		// �R���e�B�j���[���ꂽ�炻�̃X�e�[�W����n�߂邽�߂�
		// �R���e�B�j���[���ꂽ���ǂ������肷�邽�߂̃t���O��؂�ւ���
		Game::SetContinueFlag(true);
		state = _nowScene;
	}
	else if (endFlag == true)
	{
		state = SceneState::RESULT_SCENE;
	}
}