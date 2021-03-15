#pragma once

#include "ParticleEffectBase.h"

/*
@file GameClearEffect.h
@brief GameClearEffect�̐����ƍX�V���s��
*/
class GameClearEffect
	: public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    GameClearEffect(const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~GameClearEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // �g��k���ϐ�
    float mScale;
    // �����x�ϐ�
    float mAlpha;

};

