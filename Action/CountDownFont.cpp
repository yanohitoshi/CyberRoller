//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CountDownFont.h"
#include "RenderingObjectManager.h"
#include "TimeSprite.h"
#include "SpriteComponent.h"
#include "CountDownBackFont.h"
#include "WarningSprite.h"

// �ÓI�����o�[�̏�����
bool CountDownFont::timeOverFlag = false;
bool CountDownFont::countStartFlag = false;

/*
@brief	�R���X�g���N�^
@param	�J�E���g���鎞��
*/
CountDownFont::CountDownFont(int _time)
	: GameObject(false,Tag::UI)
	, AddTimeCount(60)
	, ChangeColorCount(30)
{
	// �����o�[�ϐ��̏�����
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	time = _time;
	warningFlag = false;
	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this,false,110);
	sprite->SetAlpha(1.0f);

	// �J�E���g�_�E���t�H���g�̉e����邽�߂̃o�b�N�t�H���g�𐶐�
	new CountDownBackFont(_time);
	// ���ԕ\��texture�N���X�𐶐�
	new TimeSprite();

	new WarningSprite(this);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CountDownFont::~CountDownFont()
{
	// �ÓI�����o�[�̏�����
	timeOverFlag = false;
	countStartFlag = false;
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CountDownFont::UpdateGameObject(float _deltaTime)
{
	// �Q�[���X�^�[�g������J�E���g�J�n
	if (countStartFlag == true)
	{
		// �t���[���J�E���g�𐔂���
		frameCount++;
		// �J�E���g��60�ɂȂ�����
		if (frameCount >= AddTimeCount)
		{
			// time�����炷
			time -= 1;
			frameCount = 0;
		}
	}

	// 30�ȏ�̎��͔��F�ŕ`��
	if (time > ChangeColorCount)
	{
		sprite->SetTexture(RENDERING_OBJECT_MANAGER->GetTimeTexture(time - 1));
	}
	else if (time <= ChangeColorCount && time >= 1)	// 30�ȉ��̎��͔��F�ŕ`��
	{
		// �x���t���O��true��
		warningFlag = true;
		sprite->SetTexture(RENDERING_OBJECT_MANAGER->GetTimeRedTexture(time - 1));
	}

	// texture���ɍ����vector�z��Ɋi�[���Ă���s����0��`�悷��Ƃ�null�ɃA�N�Z�X���Ă��܂��̂����
	if (time == 0)
	{
		sprite->SetTexture(RENDERING_OBJECT_MANAGER->GetTimeRedTexture(-1));
	}

	// time��-1�ȉ��ɂȂ�����^�C���I�[�o�[�ɂ���
	if (time <= -1)
	{
		timeOverFlag = true;
		sprite->SetVisible(false);
	}
}