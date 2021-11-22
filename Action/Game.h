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
	TITLE_SCENE = 0,
	// stage�I���V�[��
	STAGE_SELECT_SCENE,
	// ���X�e�[�W�V�[��
	TUTORIAL_SATGE_SCENE,
	// ���X�e�[�W�V�[��
	FIRST_SATGE_SCENE,
	// ��O�X�e�[�W�V�[��
	SECOND_SATGE_SCENE,
	// ��l�X�e�[�W�V�[��
	THIRD_SATGE_SCENE,
	// ��܃X�e�[�W�V�[��
	FOURTH_SATGE_SCENE,
	// �ŏI�X�e�[�W�V�[��
	FINAL_STAGE_SCENE,
	// ���U���g�V�[��
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
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	@param	_keyState ���͏��
	*/
	friend void ProcessInputs(const InputState& _state);


	// �V�[���J�ڂ��s���邩�ǂ����t���O
	static bool isChangeScene;


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
	int screenWidth;

	// �X�N���[���̍���
	int screenHeight;

	// �t���X�N���[�����[�h���g�p���邩�ǂ����t���O
	bool isFullScreen;

	// �t���X�N���[�����[�h�̎��̃X�N���[���̉����萔
	const int FullScreenWidth;
	// �t���X�N���[�����[�h�̎��̃X�N���[���̏c���萔
	const int FullScreenHeight;
	// �E�B���h�E���[�h�̎��̃X�N���[���̉����萔
	const int WindowScreenWidth;
	// �E�B���h�E���[�h�̎��̃X�N���[���̉����萔
	const int WindowScreenHeight;

public:

	/*
	@fn continueFlag��setter�֐�
	@brief  continueFlag�ɒl���Z�b�g
	@param  _continueFlag �R���e�B�j���[���ꂽ���ǂ���
	*/
	static void SetContinueFlag(bool _continueFlag) { continueFlag = _continueFlag; }

	/*
	@fn continueFlag��getter�֐�
	@brief  continueFlag���擾
	@return �R���e�B�j���[���ꂽ���ǂ����t���O
	*/
	static bool GetContinueFlag() { return continueFlag; }
};

