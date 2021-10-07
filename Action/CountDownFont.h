#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class Texture;
class Font;

/*
@file CountDownFont.h
@brief �J�E���g�_�E���t�H���g�̕\�����s��
*/
class CountDownFont
    : public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�J�E���g���鎞��
    */
    CountDownFont(int _time);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CountDownFont();
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;
    

private:

    // @fix
    // ���Ԑ؂�ɂȂ������ǂ����̃t���O�ϐ�
    static bool timeOverFlag;
    // �J�E���g���J�n���邩�̃t���O�ϐ�
    static bool countStartFlag;

    // SpriteComponent�ϐ�
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // �v�����鎞��
    int time;
    // WarningSpriteClass���N�����邩�ǂ����t���O
    bool warningFlag;

    // ���Ԃ�1�i�߂�^�C�~���O���r����萔
    const int AddTimeCount;
    // ���Ԑ����̐F��ύX����^�C�~���O���r����萔
    const int ChangeColorCount;

public://�Q�b�^�[�Z�b�^�[

    /*
    @fn timeOverFlag��setter�֐�
    @brief	timeOverFlag�ɒl���Z�b�g
    @param	_timeOverFlag ���Ԑ؂�ɂȂ������ǂ����̃t���O
    */
    static void SetTimeOverFlag(bool _timeOverFlag) { timeOverFlag = _timeOverFlag; }

    /*
    @fn countStartFlag��setter�֐�
    @brief	countStartFlag�ɒl���Z�b�g
    @param	_countStartFlag �J�E���g���J�n���邩�̃t���O
    */
    static void SetCountStartFlag(bool _countStartFlag) { countStartFlag = _countStartFlag; }

    /*
    @fn timeOverFlag��getter�֐�
    @brief	timeOverFlag���擾
    @return	���Ԑ؂�ɂȂ������ǂ����̃t���O
    */
    static bool GetTimeOverFlag() { return timeOverFlag; }

    /*
    @fn countStartFlag��getter�֐�
    @brief	countStartFlag���擾
    @return	�J�E���g���J�n���邩�̃t���O
    */
    static bool GetCountStartFlag() { return countStartFlag; }

    /*
    @fn warningFlag��getter�֐�
    @brief	warningFlag���擾
    @return	WarningSpriteClass���N�����邩�ǂ����t���O
    */
    bool GetWarningFlag() { return warningFlag; }

};