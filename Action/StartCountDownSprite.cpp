//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StartCountDownSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

/*
@brief	�R���X�g���N�^
*/
StartCountDownSprite::StartCountDownSprite()
	:GameObject(false, PARTICLE)
	, ChangeCount(60)
{
	// 4���texture�����[�h
	firstTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/Three.png");
	secondTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/Two.png");
	thirdTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/One.png");
	startTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/Start.png");

	// SpriteComponent��������
	sprite = new SpriteComponent(this, false);
	sprite->SetTexture(firstTexure);
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	timeStartCount = 0;
	time = 4;
	texChangeFlag = false;
	drawSpriteFlag = true;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
StartCountDownSprite::~StartCountDownSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void StartCountDownSprite::UpdateGameObject(float _deltaTime)
{
	// �`��t���O��true��������
	if (drawSpriteFlag == true)
	{
		// �J�E���g�_�E���\���p�J�E���g�𐔂���
		CheckCountProcess();

		// �e�N�X�`���̏�Ԃ��`�F�b�N
		CheckTextureProcess();
	}
}

/*
@fn �J�E���g�_�E���\�����ԃJ�E���g�𐔂���֐�
*/
void StartCountDownSprite::CheckCountProcess()
{
	// �J�E���g�v��
	++timeStartCount;
	// �J�E���g��60�ȉ���������
	if (timeStartCount >= ChangeCount)
	{
		// �`�悷��
		sprite->SetVisible(true);
		// �t���[���J�E���g�����
		frameCount++;
		// 60�t���[���ゲ�Ƃ�texture��؂�ւ���
		if (frameCount >= ChangeCount)
		{
			time -= 1;
			frameCount = 0;
			// texture�ύX�t���O��true��
			texChangeFlag = true;
		}
	}
}

/*
@fn �e�N�X�`���̏�Ԃ�����֐�
*/
void StartCountDownSprite::CheckTextureProcess()
{
	// texture�ύX�t���O��true��������
	if (texChangeFlag == true)
	{
		// ���Ԃ��Ƃ̃e�N�X�`���ɐ؂�ւ���
		ChangeTextureProcess();
	}
}

/*
@fn �e�N�X�`����؂�ւ���֐�
*/
void StartCountDownSprite::ChangeTextureProcess()
{
	// time�ϐ������Ă���ɉ�����texture���Z�b�g
	switch (time)
	{
	case TimeNum::TREE:
		sprite->SetTexture(secondTexure);
		texChangeFlag = false;
		break;
	case TimeNum::TOW:
		sprite->SetTexture(thirdTexure);
		texChangeFlag = false;
		break;
	case TimeNum::ONE:
		sprite->SetTexture(startTexure);
		// �X�^�[�gtexture�ɂȂ������̂݊g��
		SetScale(2.0f);
		texChangeFlag = false;
		break;
	case TimeNum::ZERO:
		sprite->SetVisible(false);
		drawSpriteFlag = false;
		CountDownFont::SetCountStartFlag(true);
		state = State::Dead;
		break;
	}
}