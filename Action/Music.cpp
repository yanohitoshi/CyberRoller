//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Music.h"

/*
@fn �R���X�g���N�^
@brief �~���[�W�b�N�N���X�̐������s��
*/
Music::Music()
	:music(nullptr)
{
}

/*
@fn �f�X�g���N�^
@brief �~���[�W�b�N�̉�����s��
*/
Music::~Music()
{
	Mix_FreeMusic(music);
}

/*
@fn �Đ��֐�
@brief �~���[�W�b�N���Đ����s��
*/
void Music::Play()
{
	Mix_PlayMusic(music, -1);
}

/*
@fn �t�F�[�h�C���֐�
@brief �~���[�W�b�N�̃t�F�[�h�C�����s��
*/
void Music::FadeInMusic(int fadeInTime)
{
	Mix_FadeInMusic(music, -1, fadeInTime);
}

/*
@fn �Đ��֐�
@brief �~���[�W�b�N�ǂݍ��݂��s��
@param fileName�@�ǂݍ��ރ~���[�W�b�N�t�@�C���̃p�X
@return bool true �ǂݍ��ݐ��� : false �ǂݍ��ݎ��s
*/
bool Music::LoadMusic(const std::string& fileName)
{
	music = Mix_LoadMUS(fileName.c_str());
	return music != nullptr;
}

/*
@fn ��~�֐�
@brief �~���[�W�b�N���~����
*/
void Music::Stop()
{
	Mix_HaltMusic();
}

/*
@fn �t�F�[�h�A�E�g�֐�
@brief �Đ����̃~���[�W�b�N���t�F�[�h�A�E�g����
*/
void Music::FadeOutMusic(int fadeOutTime)
{
	Mix_FadeOutMusic(fadeOutTime);
}

/*
@fn �Đ���Ԋm�F�֐�
@brief �~���[�W�b�N���Đ������ǂ����t���O�̎擾
@return bool true �Đ��� : false ��Đ���
*/
bool Music::IsPlaying()
{
	return Mix_PlayingMusic();
}
