//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "WarningSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

WarningSprite::WarningSprite(CountDownFont* _owner)
	:GameObject(false, Tag::UI)
	, ChangeFadeInValue(0.1f)
	, ChangeFadeOutValue(0.9f)
	, FadeValue(0.01f)
{
	// �ϐ��̏�����
	owner = _owner;
	alpha = 0.1f;
	count = 0;
	fadeFlag = true;
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERER->GetTexture("Assets/sprite/warning.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(true);
	sprite->SetAlpha(alpha);
}

WarningSprite::~WarningSprite()
{
}

void WarningSprite::UpdateGameObject(float _deltaTime)
{
	// count��2�ȉ�����owner�̃t���O��true�̎�
	if (count <= 2 && owner->GetWarningFlag() == true)
	{
		// ��ԃ`�F�b�N�Ǝ��ۂ̏���
		ChackFadeInOutProcess();
	}
	else if (count >= 3)	// count��3�ȏ�ɂȂ�����alpha�l��0�ɂȂ�܂�out
	{
		// �Ō�̃t�F�[�h�A�E�g����
		LastFadeOutProcess();
	}
	// fadein/out���I��邲�ƂɃJ�E���g��ǉ�
	if (fadeFlag == false && alpha <= 0.1f)
	{
		++count;
	}
	// alpha�l���Z�b�g
	sprite->SetAlpha(alpha);
}

void WarningSprite::ChackFadeInOutProcess()
{
	// �t�F�[�h�C���A�E�g����
	FadeInOutProcess();
	// �t�F�[�h�C���A�E�g�؂�ւ�����
	ChangeFadeProcess();

}

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

void WarningSprite::LastFadeOutProcess()
{
	// alpha�l��0.0f�ȏゾ������
	if (alpha >= 0.0f)
	{
		// �l������
		alpha -= FadeValue;
	}
}

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
	}
}

