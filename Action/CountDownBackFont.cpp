//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CountDownBackFont.h"
#include "GraphicsResourceManager.h"
#include "Font.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

/*
@brief	�R���X�g���N�^
@param	�J�E���g���鎞��
*/
CountDownBackFont::CountDownBackFont(int _time)
	: GameObject(false, Tag::UI)
	, AddTimeCount(60)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(695.0f, 480.0f, 0.0f));
	//  SpriteComponent������
	sprite = new SpriteComponent(this,false ,105);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	time = _time;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CountDownBackFont::~CountDownBackFont()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CountDownBackFont::UpdateGameObject(float _deltaTime)
{
	// �Q�[���X�^�[�g������J�E���g�J�n
	if (CountDownFont::GetCountStartFlag() == true)
	{
		// �t���[���J�E���g�𐔂���
		frameCount++;
		// 60�ɂȂ�����
		if (frameCount >= AddTimeCount)
		{
			// time�����炷
			time -= 1;
			frameCount = 0;
		}
	}

	// 1�ȏ�̎��͍��F�ŕ`��
	if (time >= 1)
	{
		sprite->SetTexture(GRAPHICS_RESOURCE->GetTimeBlackTexture(time - 1));
	}
	// texture���ɍ����vector�z��Ɋi�[���Ă���s����0��`�悷��Ƃ�null�ɃA�N�Z�X���Ă��܂��̂����
	if (time == 0)
	{
		sprite->SetTexture(GRAPHICS_RESOURCE->GetTimeBlackTexture(-1));
	}

	// time��-1�ȉ��ɂȂ�����^�C���I�[�o�[�ɂ���
	if (time <= -1)
	{
		sprite->SetVisible(false);
	}
}