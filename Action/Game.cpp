//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Game.h"
#include "SDL.h"
#include <SDL_mixer.h>
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "RenderingObjectManager.h"
#include "AudioResourceManager.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "TutorialStageScene.h"
#include "FirstStageScene.h"
#include "SecondStageScene.h"
#include "ThirdStageScene.h"
#include "FourthStageScene.h"
#include "FinalStageScene.h"
#include "ResultScene.h"
#include "GameObject.h"
#include "GeometryInstanceManager.h"

// �Q�[���S�̂Ō���R���e�B�j���[���ꂽ���ǂ����̔���t���O�̏�����
bool Game::continueFlag = false;

/*
@brief  �R���X�g���N�^
*/
Game::Game()
	: fps(nullptr)
    , isRunning(true)
	, screenWidth(0)
	, screenHeight(0)
	, isFullScreen(true)
	, FullScreenWidth(1920)
	, FullScreenHeight(1080)
	, WindowScreenWidth(1080)
	, WindowScreenHeight(800)
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

	// �������Ɛ������������s�������̃`�F�b�N
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	// �t���X�N���[�����ǂ����𔻒�	
	if (isFullScreen == true) // �t���X�N���[���̏ꍇ
	{
		// �X�N���[���T�C�Y���t���X�N���[���ɏ�����
		screenWidth = FullScreenWidth;
		screenHeight = FullScreenHeight;
	}
	else if (isFullScreen == false) // �t���X�N���[���łȂ��ꍇ
	{
		// �X�N���[���T�C�Y��C�ӂ̃E�B���h�E�T�C�Y�ɏ�����
		screenWidth = WindowScreenWidth;
		screenHeight = WindowScreenHeight;

	}

	// �����_���[�̏�����
	RenderingObjectManager::CreateInstance();

	// ��ʍ쐬
	// �������Ɛ������������s�������̃`�F�b�N
	if (!RENDERING_OBJECT_MANAGER->Initialize(screenWidth, screenHeight, isFullScreen))
	{
		SDL_Log("Failed to initialize renderer");
		RenderingObjectManager::DeleteInstance();
		return false;
	}

	// ���T�E���h�n��������
	// �I�[�f�B�I�Ǘ��N���X�̐���
	AudioResourceManager::CreateInstance();

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

	// �r���[�s��𐶐�����Renderer�ɓn��
	Matrix4 v = Matrix4::CreateLookAt(Vector3(-800.0f, 0.0f, -200.0f), Vector3(200.0f, 0.0f, 0.0f), Vector3::UnitZ);
	RENDERING_OBJECT_MANAGER->SetViewMatrix(v);

	// �ŏ��̃V�[���X�e�[�^�X�̏�����
	nowSceneState = TITLE_SCENE;
	// �ŏ��̃V�[���𐶐�
	nowScene = new TitleScene();

	return true;
}

/*
@brief  �I������
*/
void Game::Termination()
{
	// ���̃V�[�������
	delete nowScene;

    //�f�[�^�̃A�����[�h
	UnloadData();

    //�X�^�e�B�b�N�N���X�̉������
	// �`��N���X�̉������
	RenderingObjectManager::DeleteInstance();
	// �����蔻��N���X���������
	PhysicsWorld::DeleteInstance();
	// �T�E���h�̃��\�[�X�N���X���폜
	AudioResourceManager::DeleteInstance();
    //FPS�N���X�̉������
    delete fps;
	// ���̓N���X�̉������
    delete inputSystem;

    //�T�u�V�X�e���̏I��
	SDL_Quit();
}

/*
@brief  �Q�[�����[�v
*/
void Game::GameLoop()
{
	// �Q�[���𑱂����Ԃ̊ԃ��[�v
	while (isRunning)
	{
		// ���͊֘A�̍X�V
		UpdateInput();
		// �V�[���̍X�V
		UpdateScene();
		// �Q�[���I�u�W�F�N�g�̍X�V
		UpdateGame();
		// �`��̍X�V
		DrawGame();
		// �f���^�^�C���̍X�V
		fps->Update();
	}
}


/*
@brief   ���[�h�����f�[�^�̉��
*/
void Game::UnloadData()
{
	// RenderindObjectManager��nullptr����Ȃ�������
	if (RENDERING_OBJECT_MANAGER != nullptr)
	{
		// �f�[�^���A�����[�h
		RENDERING_OBJECT_MANAGER->UnloadData();
		// Renderer�̌�Еt�����s��
		RENDERING_OBJECT_MANAGER->Shutdown();
	}
}

/*
@brief  ���͊֘A�̍X�V����
*/
void Game::UpdateInput()
{
	// ���͍X�V
	UpdateInputSystem();
	// �Q�[���I�u�W�F�N�g�N���X�̓��͂��X�V
	UpdateGameObjectsInput();
}

/*
@brief  ���͊֘A�̏���
*/
void Game::UpdateInputSystem()
{
	// inputSystem��Update�̏���������iSDL_PollEvents�̒��O�ɌĂԁj
	inputSystem->PrepareForUpdate();

	// SDL_EVENT�̐���
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

	// ���͏�Ԃ̃A�b�v�f�[�g
	inputSystem->Update();
}

void Game::UpdateScene()
{
	// ���͏�Ԃ�ۑ�
	const InputState& state = inputSystem->GetState();

	// �����蔻�������������f�o�b�O���[�h�̐؂�ւ�
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_0) == Released)
	{
		PHYSICS->ToggleDebugMode();
	}

	// �G�X�P�[�v�܂��̓R���g���[���[�̃o�b�N�{�^���������ꂽ��Q�[�����[�v���甲����
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_BACK) == Pressed)
	{
		isRunning = false;
	}

	// �V�[���̃A�b�v�f�[�g
	nextSceneState = nowScene->Update(state);

	// ���̃V�[���Ǝ��̃V�[�����Ⴄ�܂��̓R���e�j���[���I�����ꂽ��
	if (nextSceneState != nowSceneState || Game::GetContinueFlag())
	{
		// ���̃V�[���X�e�[�^�X�Ɏ��̃V�[���X�e�[�^�X������
		nowSceneState = nextSceneState;
		// �V�[���̐؂�ւ����s��
		ChangeScene(nowSceneState, nowScene);
	}
}

/*
@brief  �Q�[���I�u�W�F�N�g�̓��͏���
*/
void Game::UpdateGameObjectsInput()
{
	// �����V�[���J�ڂ��s���Ȃ��ꍇ�I�u�W�F�N�g�ɓ��͏�Ԃ�n���čX�V
	if (nextSceneState == nowSceneState && Game::GetContinueFlag() == false)
	{
		GameObjectInputs(inputSystem->GetState());
	}
}

/*
@fn �V�[���ύX�֐�
@brief �O�̃V�[���̉���Ǝ��̃V�[���̐������s��
@param _state �V�[���̏��
@param _scene �i�s���̃V�[���̃|�C���^
*/
void Game::ChangeScene(SceneState _state, BaseScene* _scene)
{
	// ���݂̃V�[���̍폜���s��
	RemoveScene(_scene);
	// ���̃V�[���𐶐�����
	CreateScene(_state);
}

/*
@fn �V�[���̐������s���֐�
*/
void Game::CreateScene(SceneState _state)
{
	// _state���Q�Ƃ��ĕK�v�ȃV�[���𐶐�
	switch (_state)
	{
	case SceneState::TITLE_SCENE:
		nowScene = new TitleScene();
		break;
	case SceneState::TUTORIAL_SATGE_SCENE:
		nowScene = new TutorialStageScene();
		break;
	case SceneState::STAGE_SELECT_SCENE:
		nowScene = new StageSelectScene();
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
	case SceneState::FOURTH_SATGE_SCENE:
		nowScene = new FourthStageScene();
		break;
	case SceneState::FINAL_STAGE_SCENE:
		nowScene = new FinalStageScene();
		break;
	case SceneState::RESULT_SCENE:
		nowScene = new ResultScene();
		break;
	}
}

/*
@fn �V�[���̍폜���s���֐�
*/
void Game::RemoveScene(BaseScene* _scene)
{
	// �V�[���ύX���������ۂɑS�Ă̎g�p�ς݃I�u�W�F�N�g���폜
	GameObject::RemoveUsedGameObject();
	// �V�[���̃�������delete
	delete _scene;

	// �W�I���g���C���X�^���X�Ƀ}�b�v�Ɋi�[����Ă���Q�[���I�u�W�F�N�g�N���X���폜
	RENDERING_OBJECT_MANAGER->GetGeometryInstanceManager()->ClearGeometryInstanceGameObjectMap();
	// �V�[���J�ڔ���Ɏg�p����t���O��������
	continueFlag = false;
}

/*
@brief  �`��֘A�̏���
*/
void Game::DrawGame()
{
	// �`�揈��
	RENDERING_OBJECT_MANAGER->Draw();
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

/*
@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
@param	�Ō�̃t���[������������̂ɗv��������
*/
void UpdateGameObjects(float _deltaTime)
{
	// �I�u�W�F�N�g�̍X�V�t���O��true��
	GameObject::updatingGameObject = true;
	
	// gameObjectMap���ɑ��݂���S�ẴI�u�W�F�N�g���X�V
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			// object�̍X�V�����Ăяo��
			gameObject->Update(_deltaTime);
		}
	}

	// �r���ǉ����ꂽobject�̍X�V����
	// �����[�v����gameObjectMap�֍��������Ă��܂��ƓY����������ė�O���X���[���Ă��܂��̂ŁA
	// ��x�ʂ�vector���ōX�V���Ă��̌㍇��������
	for (auto pending : GameObject::pendingGameObjects)
	{
		// �X�V����
		// WorldTransform���X�V
		pending->ComputeWorldTransform();

		// �}�b�v�ɒǉ�
		// �ǉ������I�u�W�F�N�g�Ɠ�����ނ̃I�u�W�F�N�g�ϒ��R���e�i�����łɂ��邩�ǂ���Tag��p���Ĕ���
		auto gameObjects = GameObject::gameObjectMap.find(pending->GetTag());
		if (gameObjects != GameObject::gameObjectMap.end())
		{
			// �R���e�i�����������炻�̃R���e�i�ɒǉ�
			gameObjects->second.emplace_back(pending);
		}
		else  
		{
			// �R���e�i��������Ȃ������ꍇ�̈ꎞ�ۑ��R���e�i
			std::vector<GameObject*> tmpVector;
			// �ꎞ�ۑ��R���e�i�ɒǉ�
			tmpVector.emplace_back(pending);
			// �ꎞ�I�ɕۑ����Ă����R���e�i��map�ɒǉ�����
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
			// �X�e�[�^�X��Dead��������
			if (gameObject->GetState() == State::Dead )
			{
				// Dead��ԃI�u�W�F�N�g�p�ϒ��R���e�i�Ɋi�[
				deadObjects.emplace_back(gameObject);
			}
		}
	}

	// �T���I�������deadObjects���̃I�u�W�F�N�g���폜
	while (!deadObjects.empty())
	{
		// �폜
		deadObjects.pop_back();
	}

	// ���S��Ԃ̃I�u�W�F�N�g�p�z����N���A
	deadObjects.clear();
}

/*
@brief  �Q�[���I�u�W�F�N�g�̓��͏���
@param	_keyState ���͏��
*/
void GameObjectInputs(const InputState& _state)
{
	// �I�u�W�F�N�g�̍X�V�t���O��true��
	GameObject::updatingGameObject = true;

	// �������Ă���I�u�W�F�N�g�̓��͏�Ԃ��X�V
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			// object�̓��͏����Ăяo��
			gameObject->ProcessInput(_state);
		}
	}
	
	// �X�V�t���O��false��
	GameObject::updatingGameObject = false;
}