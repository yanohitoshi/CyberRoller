#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Math.h"

// �N���X�̑O���錾
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
	: MAX_LIGHT(0.8f),
	  CLEAR_TO_CHANGE_SCENE(120),
	  CHOICE_CONTINUE_COUNT(90),
	  CONTINUE_TO_CHANGE_SCENE(360),
	  TIMEOVERS_LIGHT(Vector3(0.3f, 0.3f, 0.3f)),
	  CHANGE_LIGHT_SPEED(Vector3(0.01f, 0.01f, 0.01f))
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
	virtual SceneState Update(const InputState& state) = 0;


protected:

	// ���C�g�pVector3�ϐ�
	Vector3 light;
	// �N���A��̃J�E���g
	int clearCount;
	// �؂�ւ��p�J�E���g
	int changeCount;
	// �V�[�����n�܂������ǂ����t���O
	bool startScene;
	// �R���e�j���[���ꂽ���t���O
	bool isContinueFlag;
	// �I���t���O
	bool endFlag;
	// ���C�g�𗎂Ƃ����ǂ����t���O
	bool lightDownFlag;

	// ���C�g�̋����̍ő�l
	const float MAX_LIGHT;
	// �N���A�������̃V�[�����J�ڂ���܂ł̃J�E���g
	const int CLEAR_TO_CHANGE_SCENE;
	// �R���e�j���[�I����Ԃɓ���܂ł̃J�E���g
	const int CHOICE_CONTINUE_COUNT;
	// �R���e�j���[�I����A���̃V�[���ɑJ�ڂ���܂ł̃J�E���g
	const int CONTINUE_TO_CHANGE_SCENE;
	// �^�C���I�[�o�[���̃��C�g�̖��邳
	const Vector3 TIMEOVERS_LIGHT;
	// ���C�g�A�b�v�E�_�E�����̕ύX���x
	const Vector3 CHANGE_LIGHT_SPEED;

private:


};

