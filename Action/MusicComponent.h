#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "AudioComponent.h"

// class�̑O���錾
class Music;

/*
@file MusicComponent.h
@brief BGM���X�V����N���X
*/
class MusicComponent :
    public AudioComponent
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
    @param	�ǂݍ��ރT�E���h�t�@�C���̃p�X
    @param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
    */
	MusicComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder = 100);

	/*
	@fn �f�X�g���N�^
	@brief  component�̍폜���s��
	*/
	~MusicComponent()override;

    /*
    @fn �t�F�[�h�C���Đ��֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N�̃t�F�[�h�C���Đ����s��
    @param fadeInTime�@�t�F�[�h�C���ɂ����鎞��
    */
    void PlayFadeIn(int _fadeInTime);

    /*
    @fn �Đ��֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N���Đ����s��
    */
    void Play();

    /*
    @fn �t�F�[�h�A�E�g�֐�(�~���[�W�b�N)
    @brief �Đ����̃~���[�W�b�N�̃t�F�[�h�A�E�g���s��
    @param fadeOutTime�@�t�F�[�h�A�E�g�ɂ����鎞��
    */
    void FadeOut(int _fadeOutTime);

    /*
    @fn ��~�֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N���~���s��
    */
    void Stop();

    /*
    @fn �Đ���Ԋm�F�֐�(�~���[�W�b�N)
    @brief �~���[�W�b�N���Đ������ǂ����t���O�̎擾
    @return bool true �Đ��� : false ��Đ���
    */
    bool IsPlaying();

private:

    // �������S������Music�N���X�̃|�C���^
	Music* myMusic;
};