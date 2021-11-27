//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SDL.h"
#include "FPS.h"
#include "stdio.h"

/*
@fn �R���X�g���N�^
*/
FPS::FPS()
	: setFps(60)
	, oneFrameTickCount(1000 / setFps)
	, fpsCount(0)
	, frameStartTickTime(0)
	, fps(0)
    , beforetickCount(0)
	, deltaTime(0)
{
}

/*
@fn �f�X�g���N�^
*/
FPS::~FPS()
{
}

/*
@brief	�t���[�����̏���
*/
void FPS::Update()
{
	Wait();
	deltaTime = (SDL_GetTicks() - beforetickCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	beforetickCount = SDL_GetTicks();
	//1�t���[���ڂ̎�����ۑ�
	if (fpsCount == 0)
	{
		frameStartTickTime = SDL_GetTicks();
	}
	//�ݒ肵���t���[�������o�߂�����
	if (fpsCount == setFps)
	{
		int nowTickTime = SDL_GetTicks();
		fps = 1000 / ((nowTickTime - frameStartTickTime) / setFps);
		fpsCount = 0;
	}
	else
	{
		fpsCount++;
	}
}

/*
@brief	FPS���ݒ�l���傫���Ȃ�Ȃ����߂̐���
*/
void FPS::Wait()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), beforetickCount + oneFrameTickCount));
}