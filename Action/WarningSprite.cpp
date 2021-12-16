//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "WarningSprite.h"
#include "GraphicsResourceManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"
#include "SoundEffectComponent.h"

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
	isPlaySound = true;

	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this, false);
	Texture* tex = GRAPHICS_RESOURCE->CreateTexture("Assets/sprite/information/warning.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(true);
	sprite->SetAlpha(alpha);

	// �T�E���h�G�t�F�N�g�𐶐�
	soundEffect = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Time/Warning.wav");
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
	// �T�E���h���Đ���������𔻒�
	if (owner->GetWarningFlag() && isPlaySound)
	{
		// �T�E���h���Đ�
		soundEffect->Play();
		// �Đ����Ȃ���Ԃɂ���
		isPlaySound = false;
	}

	// count��2�ȉ�����owner�̃t���O��true�̎�
	if (fadeinCount <= 2 && owner->GetWarningFlag())
	{
		// ��ԃ`�F�b�N�Ǝ��ۂ̏���
		CheckFadeInOutProcess();
	}
	else if (fadeinCount >= 3)	// count��3�ȏ�ɂȂ�����alpha�l��0�ɂȂ�܂�out
	{
		// �T�E���h�����Ă�����
		if (soundEffect->IsPlaying())
		{
			// �T�E���h���~����
			soundEffect->Stop();
		}
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