//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "WarningSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

/*
@fn �R���X�g���N�^
@brief	�R���X�g���N�^
@param	�e�ƂȂ�CountDownFont�^�|�C���^
*/
WarningSprite::WarningSprite(CountDownFont* _owner)
	:GameObject(false, Tag::UI)
	, ChangeFadeInValue(0.1f)
	, ChangeFadeOutValue(0.9f)
	, FadeValue(0.01f)
{
	// �ϐ��̏�����
	owner = _owner;
	alpha = 0.1f;
	fadeinCount = 0;
	fadeFlag = true;
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERER->GetTexture("Assets/sprite/information/warning.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(true);
	sprite->SetAlpha(alpha);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
WarningSprite::~WarningSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void WarningSprite::UpdateGameObject(float _deltaTime)
{
	// count��2�ȉ�����owner�̃t���O��true�̎�
	if (fadeinCount <= 2 && owner->GetWarningFlag() == true)
	{
		// ��ԃ`�F�b�N�Ǝ��ۂ̏���
		CheckFadeInOutProcess();
	}
	else if (fadeinCount >= 3)	// count��3�ȏ�ɂȂ�����alpha�l��0�ɂȂ�܂�out
	{
		// �Ō�̃t�F�[�h�A�E�g����
		LastFadeOutProcess();
	}

	// alpha�l���Z�b�g
	sprite->SetAlpha(alpha);
}

/*
@fn �t�F�[�h�C���A�E�g�̏�Ԃ�����֐�
*/
void WarningSprite::CheckFadeInOutProcess()
{
	// �t�F�[�h�C���A�E�g����
	FadeInOutProcess();
	// �t�F�[�h�C���A�E�g�؂�ւ�����
	ChangeFadeProcess();

}

/*
@fn �t�F�[�h�C���A�E�g�����֐�
*/
void WarningSprite::FadeInOutProcess()
{
	// fadeFlag��true��������fadein
	if (fadeFlag == true)
	{
		alpha += FadeValue;
	}
	else if (fadeFlag == false)		// fadeFlag��false��������fadeout
	{
		alpha -= FadeValue;
	}
}

/*
@fn �Ō�̃t�F�[�h�A�E�g�����֐�
*/
void WarningSprite::LastFadeOutProcess()
{
	// alpha�l��0.0f�ȏゾ������
	if (alpha >= 0.0f)
	{
		// �l������
		alpha -= FadeValue;
	}
}

/*
@fn �t�F�[�h�C���A�E�g�̐؂�ւ������֐�
*/
void WarningSprite::ChangeFadeProcess()
{
	// alpha�l������in/out��؂�ւ�
	if (alpha <= ChangeFadeInValue)
	{
		// �t���O��in��Ԃł���true�ɕύX
		fadeFlag = true;
	}
	else if (alpha >= ChangeFadeOutValue)
	{
		// �t���O��out��Ԃł���false�ɕύX
		fadeFlag = false;
		++fadeinCount;
	}
}