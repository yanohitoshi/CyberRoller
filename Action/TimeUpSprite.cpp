//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TimeUpSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

// static�����o�[��������
bool TimeUpSprite::drawFlag = true;

/*
@fn �R���X�g���N�^
*/
TimeUpSprite::TimeUpSprite()
	:GameObject(false, Tag::UI)
	, DrawCount(120)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent������
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/timeup.png");
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
TimeUpSprite::~TimeUpSprite()
{
	// �ÓI�ϐ�������
	drawFlag = true;
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TimeUpSprite::UpdateGameObject(float _deltaTime)
{
	// �^�C���I�[�o�[����1�x�����`��t���O��true��������
	if (CountDownFont::GetTimeOverFlag() == true && visibleFlag == true)
	{
		// �t���[���J�E���g�v��
		++frameCount;
		// �`�悷��
		sprite->SetVisible(true);
		// �t���[���J�E���g��120�𒴂�����
		if (frameCount >= DrawCount)
		{
			//�@1�x�����`��t���O��false��
			visibleFlag = false;
			// �`���؂�
			sprite->SetVisible(false);
			// �`�悳��Ă��邩�t���O��false��
			drawFlag = false;
		}
	}
}