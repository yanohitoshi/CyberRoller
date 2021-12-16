#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Math.h"

// �N���X�̑O���錾
class PlayerObject;
struct InputState;
enum SceneState;

/*
@file BaseScene.h
@brief Scene�̊��N���X
*/
class BaseScene
{
public:

	// �R���X�g���N�^
	BaseScene()
	: MaxLight(0.8f)
	, ClearToChangeSceneTime(360)
	, ChoiceContinueCount(90)
	, ContinueToChangeScene(360)
	, TimeoversLight(Vector3(0.3f, 0.3f, 0.3f))
	, ChangeLightSpeed(Vector3(0.01f, 0.01f, 0.01f))
	, isSceneClear(false)
	{};

	/*
	@fn �f�X�g���N�^(���z�֐�)
	@brief  scene�̍폜���s��
	*/
	virtual ~BaseScene() {};

	/*
	@fn�@�V�[���̃A�b�v�f�[�g�֐�(�������z�֐�)
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	virtual SceneState Update(const InputState& _inputState) = 0;


protected:

	/*
	@fn �V�[���J�n���̃��C�g�A�b�v�֐�
	*/
	void StartSceneLightUp();

	/*
	@fn �N���A�������̃`�F�b�N�ƃN���A�J�E���g�𐔂��鏈���֐�
	@param _playerObject �V�[���ɑ��݂���v���C���[�̃|�C���^
	*/
	void SceneClearCount(PlayerObject* _playerObject);

	/*
	@fn �R���e�B�j���[�I�������֐�
	@param _inputState ���͏��
	*/
	void ContinueSelect(const InputState& _inputState);

	/*
	@fn �R���e�B�j���[�I�����̃��C�g�J�ڊ֐�
	*/
	void LightTransitionAtContinue();
	
	/*
	@fn �R���e�B�j���[�I����̃V�[���X�e�[�^�X�ύX�����֐�
	@param _nowScene �R���e�B�j���[���I�����ꂽ�ꍇ���̃V�[���̃X�e�[�^�X���K�v�Ȃ��ߍ��̃X�e�[�^�X�����炤
	*/
	void SceneStateChangeAtContinue(SceneState _nowScene);

	// �X�e�[�W�N���G�C�^�[����v���C���[�̃|�C���^�����炤���߂̕ϐ�
	PlayerObject* playerObject;

	// �V�[���X�e�[�^�X���Ǘ����邽�߂̕ϐ�
	SceneState state;

	// ���C�g�pVector3�ϐ�
	Vector3 light;
	// �N���A��̃J�E���g
	int clearCount;
	// �R���e�B�j���[�I����̐؂�ւ��p�J�E���g
	int changeCount;
	// �V�[�����n�܂������ǂ����t���O
	bool startScene;
	// �R���e�j���[���ꂽ���t���O
	bool isContinueFlag;
	// �I���t���O
	bool isEndFlag;
	// ���C�g�𗎂Ƃ����ǂ����t���O
	bool lightDownFlag;
	// �V�[�����N���A�������ǂ���
	bool isSceneClear;
	// �^�C���I�[�o�[�ɂȂ�����
	bool isTimeOver;

	// ���C�g�̋����̍ő�l
	const float MaxLight;
	// �N���A�������̃V�[�����J�ڂ���܂ł̃J�E���g
	const int ClearToChangeSceneTime;
	// �R���e�j���[�I����Ԃɓ���܂ł̃J�E���g
	const int ChoiceContinueCount;
	// �R���e�j���[�I����A���̃V�[���ɑJ�ڂ���܂ł̃J�E���g
	const int ContinueToChangeScene;
	// �^�C���I�[�o�[���̃��C�g�̖��邳
	const Vector3 TimeoversLight;
	// ���C�g�A�b�v�E�_�E�����̕ύX���x
	const Vector3 ChangeLightSpeed;

public:

	/*
	@fn �V�[�����n�܂������ǂ����t���O��getter
	@return �V�[�����n�܂������ǂ���
	*/
	bool GetStartScene() { return startScene; }

	/*
	@fn �V�[�����N���A�������ǂ����t���O��getter
	@return �V�[�����N���A�������ǂ���
	*/
	bool GetIsSceneClear() { return isSceneClear; }

	/*
	@fn �^�C���I�[�o�[�ɂȂ������t���O��getter
	@return �^�C���I�[�o�[�ɂȂ�����
	*/
	bool GetIsTimeOver() { return isTimeOver; }

	/*
	@fn �R���e�j���[���ꂽ���t���O��getter
	@return �R���e�j���[���ꂽ��
	*/
	bool GetIsContinueFlag() { return isContinueFlag; }

	/*
	@fn �I���t���O��getter
	@return �I�����Ă��邩�ǂ���
	*/
	bool GetIsEndFlag() { return isEndFlag; }
};