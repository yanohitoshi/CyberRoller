#include "StartCountDownSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

StartCountDownSprite::StartCountDownSprite()
	:GameObject(false, PARTICLE)
	, ChangeCount(60)
{
	// 4���texture�����[�h
	firstTexure = RENDERER->GetTexture("Assets/sprite/CountDown3.png");
	secondTexure = RENDERER->GetTexture("Assets/sprite/CountDown2.png");
	thirdTexure = RENDERER->GetTexture("Assets/sprite/CountDown1.png");
	startTexure = RENDERER->GetTexture("Assets/sprite/Start.png");

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

StartCountDownSprite::~StartCountDownSprite()
{
}

void StartCountDownSprite::UpdateGameObject(float _deltaTime)
{
	// �`��t���O��true��������
	if (drawSpriteFlag == true)
	{
		// �J�E���g�_�E���\���p�J�E���g�𐔂���
		ChackCountProcess();

		// �e�N�X�`���̏�Ԃ��`�F�b�N
		ChackTextureProcess();
	}
}

void StartCountDownSprite::ChackCountProcess()
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

void StartCountDownSprite::ChackTextureProcess()
{
	// texture�ύX�t���O��true��������
	if (texChangeFlag == true)
	{
		// ���Ԃ��Ƃ̃e�N�X�`���ɐ؂�ւ���
		ChangeTextureProcess();
	}
}

void StartCountDownSprite::ChangeTextureProcess()
{
	// time�ϐ������Ă���ɉ�����texture���Z�b�g
	// 3�̎�
	if (time == 3)
	{
		sprite->SetTexture(secondTexure);
		texChangeFlag = false;
	}

	// 2�̎�
	if (time == 2)
	{
		sprite->SetTexture(thirdTexure);
		texChangeFlag = false;
	}

	// 1�̎�
	if (time == 1)
	{
		sprite->SetTexture(startTexure);
		texChangeFlag = false;
	}

	// 0�ɂȂ�����`���؂���state��Dead��
	if (time == 0)
	{
		sprite->SetVisible(false);
		drawSpriteFlag = false;
		CountDownFont::SetCountStartFlag(true);
		state = State::Dead;
	}
}
