//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ContinueSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"
#include "TimeUpSprite.h"

// �ÓI�����o�[������
bool ContinueSprite::drawFlag = true;
bool ContinueSprite::continueFlag = true;

/*
@brief	�R���X�g���N�^
*/
ContinueSprite::ContinueSprite()
	:GameObject(false, Tag::UI)
	, DrawCount(60)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// texture�����[�h
	Texture* tex = RENDERING_OBJECT_MANAGER->CreateTexture("Assets/sprite/information/continue.png");
	// SpriteComponent��������
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
	visibleFlag = true;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ContinueSprite::~ContinueSprite()
{
	// �ÓI�����o�[������
	drawFlag = true;
	continueFlag = true;
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ContinueSprite::UpdateGameObject(float _deltaTime)
{
	// �^�C���A�b�v��Ԓ��^�C���A�b�v�摜�̕`�悪�I�������`�悷��
	if (TimeUpSprite::GetDrawFlag() == false && visibleFlag == true)
	{
		sprite->SetVisible(true);
		++frameCount;
	}
}

/*
@brief	����
@param	���͏��
*/
void ContinueSprite::GameObjectInput(const InputState& _keyState)
{
	// �^�C���A�b�v�摜�̕`�悪�I����ăR���e�j���[�摜�`��J�n�����莞�Ԃ����Ă�����
	if (TimeUpSprite::GetDrawFlag() == false && frameCount >= DrawCount)
	{
		CheckKeyProcess(_keyState);
	}
}

/*
@brief	���͏������ɕ`���؂�ւ���
@param	���͏��
*/
void ContinueSprite::CheckKeyProcess(const InputState& _keyState)
{
	// A�{�^���������ꂽ��
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
	{
		// �`���؂��ăR���e�j���[�t���O��true��
		sprite->SetVisible(false);
		visibleFlag = false;
		drawFlag = false;
		continueFlag = true;
	}
	else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed) // B�{�^���������ꂽ��
	{
		// �`���؂��ăR���e�j���[�t���O��false��
		sprite->SetVisible(false);
		visibleFlag = false;
		drawFlag = false;
		continueFlag = false;
	}
}