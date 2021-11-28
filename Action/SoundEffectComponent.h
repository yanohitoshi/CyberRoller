#pragma once
#include "AudioComponent.h"

class Sound;

class SoundEffectComponent :
    public AudioComponent
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
    @param	�T�E���h�̃t�@�C���p�X
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	SoundEffectComponent(GameObject* _owner, const std::string& _fileName,int _updateOrder = 100);

	/*
	@fn �f�X�g���N�^
	@brief  component�̍폜���s��
	*/
	~SoundEffectComponent()override;

    /*
    @fn �Đ��֐�(�T�E���h)
    @brief �T�E���h�̍Đ����s��
    */
    void Play();

    /*
    @fn ��~�֐�(�T�E���h)
    @brief �T�E���h�̒�~���s��
    */
    void Stop();

    /*
    @fn �Đ���Ԋm�F�֐�(�T�E���h)
    @brief �w�肵���T�E���h���Đ������ǂ����t���O�̎擾
    @return bool true �Đ��� : false ��Đ���
    */
    bool IsPlaying();

private:

	Sound* mySound;
};