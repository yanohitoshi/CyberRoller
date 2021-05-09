#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "InputSystem.h"


// �N���X�̑O���錾
class FPS;
class GameObject;
class InputSystem;
class GameScene;
class BaseScene;

/*
@enum�@�V�[���̏�Ԃ������^�O
*/
enum SceneState
{
	// �^�C�g���V�[��
	TITLE_SCENE,
	// ���X�e�[�W�V�[��
	FIRST_SATGE_SCENE,
	// ���X�e�[�W�V�[��
	SECOND_SATGE_SCENE,
	// ��O�X�e�[�W�V�[��
	THIRD_SATGE_SCENE,
	// �ŏI�X�e�[�W�V�[��
	FINAL_STAGE_SCENE,
	// �N���A�V�[��
	CLEAR_SCENE,
	// �Q�[���I�[�o�[�V�[��
	OVER_SCENE,
	// ���U���g�X�e�[�W�V�[��
	RESULT_SCENE
};

/*
@file Game.h
@brief �Q�[���̐i�s���s��
*/
class Game
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	Game();
	/*
	@fn �f�X�g���N�^
	*/
	~Game();

    /*
    @brief	����������
    @return true : ����, false : ���s
    */
	bool Initialize();

	/*
	@brief  �I������
	*/
	void Termination();

	/*
	@brief  �Q�[�����[�v
	*/
	void GameLoop();

	/*
	@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	*/
	friend void ProcessInputs(const InputState& _state);

	/*
	@brief  continueFlag��setter
	@param  _continueFlag �R���e�B�j���[���ꂽ���ǂ���
	*/
	static void SetContinueFlag(bool _continueFlag) { continueFlag = _continueFlag; }
	/*
	@brief  continueFlag��getter
	@return �R���e�B�j���[���ꂽ���ǂ����t���O
	*/
	static bool GetContinueFlag() { return continueFlag; }

	// �V�[���J�ڂ��s���邩�ǂ����t���O
	static bool isChangeScene;

	static int debug;

private:

	// �Q�[���v���C���̃V�[��
	BaseScene* nowScene;

	// �V�[���̏�Ԃ�ۑ�����ϐ�
	SceneState nowSceneState;
	
	/*
	@brief  ���͊֘A�̏���
	*/
    void ProcessInput();
	
	/*
	@brief  �`��֘A�̏���
	*/
    void GenerateOutput();

	/*
	@brief  �Q�[���̃A�b�v�f�[�g����
	*/
	void UpdateGame();

	/*
	@brief   ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	/*
	@fn �V�[���ύX�֐�
	@brief �O�̃V�[���̉���Ǝ��̃V�[���̐������s��
	@param _state �V�[���̏��
	@param _scene �i�s���̃V�[���̃|�C���^
	*/
	void ChangeScene(SceneState _state,BaseScene* _scene);

	// FPS�v���N���X
	FPS* fps;

    // ���͊Ǘ��N���X
	InputSystem* inputSystem;

	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;

	// �R���e�j���[���ꂽ���t���O
	static bool continueFlag;

	// �X�N���[���̕�
	float screenWidth;

	// �X�N���[���̍���
	float screenHeight;

	// �t���X�N���[�����[�h���g�p���邩�ǂ����t���O
	bool isFullScreen;

	// �t���X�N���[�����[�h�̎��̃X�N���[���̉����萔
	const float FullScreenWidth;
	// �t���X�N���[�����[�h�̎��̃X�N���[���̏c���萔
	const float FullScreenHeight;
	// �E�B���h�E���[�h�̎��̃X�N���[���̉����萔
	const float WindowScreenWidth;
	// �E�B���h�E���[�h�̎��̃X�N���[���̉����萔
	const float WindowScreenHeight;
};

