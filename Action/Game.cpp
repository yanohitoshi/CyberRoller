#include "Game.h"
#include "SDL.h"
#include <SDL_mixer.h>
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "FirstStageScene.h"
#include "SecondStageScene.h"
#include "ThirdStageScene.h"
#include "FinalStageScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"
#include "ResultScene.h"
#include "GameObject.h"

int Game::debug = 0;
// �V�[���`�F���W���s�����t���O�̏�����
bool Game::isChangeScene = false;
// �Q�[���S�̂Ō���R���e�B�j���[���ꂽ���ǂ����̔���t���O�̏�����
bool Game::continueFlag = false;

/*
@brief  �R���X�g���N�^
*/
Game::Game()
	: fps(nullptr)
    , isRunning(true)
	, screenWidth(0.0f)
	, screenHeight(0.0f)
	, isFullScreen(true)
{
}

/*
@brief  �f�X�g���N�^
*/
Game::~Game()
{
}

/*
@brief  ����������
@return true : ���� , false : ���s
*/
bool Game::Initialize()
{
	//SDL�̏�����
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

    //���͊Ǘ��N���X�̏�����
	inputSystem = new InputSystem();
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	if (isFullScreen == true)
	{
		screenWidth = 1920;
		screenHeight = 1080;
	}
	else if (isFullScreen == false)
	{
		screenWidth = 1080;
		screenHeight = 800;

	}

	//�����_���[�̏�����
	Renderer::CreateInstance();
	//��ʍ쐬
	if (!RENDERER->Initialize(screenWidth, screenHeight, isFullScreen))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

	AudioManager::CreateInstance();
	// �T�E���h�̏�����
	if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG))
	{
		return false;
	}
	// SDLMixer API�������@44100:�����̎��g�� 2:�X�e���I 4096:�����o�b�t�@�T�C�Y
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		Mix_CloseAudio();
		Mix_Quit();
		return false;
	}
	int decordNum = Mix_GetNumMusicDecoders();
	for (int i = 0; i < decordNum; ++i)
	{
		printf("MusicDecorder %d : %s\n", i, Mix_GetMusicDecoder(i));
	}
	int chunkNum = Mix_GetNumChunkDecoders();
	for (int i = 0; i < chunkNum; ++i)
	{
		printf("SoundDecorder %d : %s\n", i, Mix_GetChunkDecoder(i));
	}


    //�����蔻��p�N���X�̏�����
	PhysicsWorld::CreateInstance();


	//FPS�Ǘ��N���X�̏�����
	fps = new FPS();

	Matrix4 v = Matrix4::CreateLookAt(Vector3(200, 0, -500), Vector3(200,0, 0),Vector3::UnitY);
	RENDERER->SetViewMatrix(v);

	nowSceneState = TITLE_SCENE;
	nowScene = new TitleScene();

	return true;
}

/*
@brief  �I������
*/
void Game::Termination()
{
	delete nowScene;
    //�f�[�^�̃A�����[�h
	UnloadData();
    //�X�^�e�B�b�N�N���X�̉������
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
    //�N���X�̉������
    delete fps;
    delete inputSystem;
    //�T�u�V�X�e���̏I��
	SDL_Quit();
}

/*
@brief  �Q�[�����[�v
*/
void Game::GameLoop()
{
	while (isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		fps->Update();
		if (isChangeScene == true)
		{
			ChangeScene(nowSceneState, nowScene);
			isChangeScene = false;
			continueFlag = false;
		}
	}
}


/*
@brief   ���[�h�����f�[�^�̉��
*/
void Game::UnloadData()
{
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();
		RENDERER->Shutdown();
	}
}


/*
@brief  ���͊֘A�̏���
*/
void Game::ProcessInput()
{
	inputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			inputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	inputSystem->Update();
	const InputState& state = inputSystem->GetState();

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_BACK) == Pressed)
	{
		isRunning = false;
	}

	SceneState tmpSceneState;

	tmpSceneState = nowScene->Update(state);

	if (isChangeScene == false && Game::GetContinueFlag() == false)
	{
		ProcessInputs(state);
	}

	if (tmpSceneState != nowSceneState || Game::GetContinueFlag())
	{
		nowSceneState = tmpSceneState;
		isChangeScene = true;
	}
}

void Game::ChangeScene(SceneState _state, BaseScene* _scene)
{
	// �V�[���ύX���������ۂɑS�Ă̎g�p�ς݃I�u�W�F�N�g���폜
	GameObject::RemoveUsedGameObject();
	// �V�[���̃�������delete
	delete _scene;

	// _state���Q�Ƃ��ĕK�v�ȃV�[���𐶐�
	switch (_state)
	{
	case SceneState::TITLE_SCENE:
		nowScene = new TitleScene();
		break;
	case SceneState::FIRST_SATGE_SCENE:
		nowScene = new FirstStageScene();
		break;
	case SceneState::SECOND_SATGE_SCENE:
		nowScene = new SecondStageScene();
		break;
	case SceneState::THIRD_SATGE_SCENE:
		nowScene = new ThirdStageScene();
		break;
	case SceneState::FINAL_STAGE_SCENE:
		nowScene = new FinalStageScene();
		break;
	case SceneState::CLEAR_SCENE:
		nowScene = new ClearScene();
		break;
	case SceneState::OVER_SCENE:
		nowScene = new GameOverScene();
		break;
	case SceneState::RESULT_SCENE:
		nowScene = new ResultScene();
		break;

	}
}

/*
@brief  �`��֘A�̏���
*/
void Game::GenerateOutput()
{
	// �`�揈��
	RENDERER->Draw();
}

/*
@brief  �Q�[���̃A�b�v�f�[�g����
*/
void Game::UpdateGame()
{
	// �f���^�^�C���̍X�V
	float deltaTime = fps->GetDeltaTime();
	// GameObjects�̍X�V������
	UpdateGameObjects(deltaTime);
}

void UpdateGameObjects(float _deltaTime)
{
	// �I�u�W�F�N�g�̍X�V�t���O��true��
	GameObject::updatingGameObject = true;
	
	// gameObjectMap���ɑ��݂���S�ẴI�u�W�F�N�g���X�V
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			gameObject->Update(_deltaTime);
		}
	}

	// �r���ǉ����ꂽobject�̍X�V����
	// �����[�v����gameObjectMap�ɍ��������Ă��܂��ƓY����������ė�O���X���[���Ă��܂��̂ň�x�ʂ�vector���ōX�V���Ă��̌㍇��������
	for (auto pending : GameObject::pendingGameObjects)
	{
		// �X�V����
		pending->ComputeWorldTransform();
		// �}�b�v�ɒǉ�
		auto gameObjects = GameObject::gameObjectMap.find(pending->GetTag());
		if (gameObjects != GameObject::gameObjectMap.end())
		{
			gameObjects->second.emplace_back(pending);
		}
		else
		{
			std::vector<GameObject*> tmpVector;
			tmpVector.emplace_back(pending);
			GameObject::gameObjectMap[pending->GetTag()] = tmpVector;
		}
		// �g�p�ςݔz����N���A
		GameObject::pendingGameObjects.clear();
	}
	// �X�V�t���O��false��
	GameObject::updatingGameObject = false;

	// ���S��Ԃ̃I�u�W�F�N�g�pvector���쐬
	std::vector<class GameObject*>deadObjects;
	// gameObjectMap���玀��ł���I�u�W�F�N�g��T���Ď��S��Ԃ̃I�u�W�F�N�g�pvector�ɒǉ�
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			if (gameObject->GetState() == State::Dead )
			{
				deadObjects.emplace_back(gameObject);
			}
		}
	}

	// �T���I�������deadObjects���̃I�u�W�F�N�g���폜
	while (!deadObjects.empty())
	{
		deadObjects.pop_back();
	}

	// �z����N���A
	deadObjects.clear();
}

void ProcessInputs(const InputState& _state)
{
	// �I�u�W�F�N�g�̍X�V�t���O��true��
	GameObject::updatingGameObject = true;

	// �������Ă���I�u�W�F�N�g�̓��͏�Ԃ��X�V
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			gameObject->ProcessInput(_state);
		}
	}
	// �X�V�t���O��false��
	GameObject::updatingGameObject = false;

}
