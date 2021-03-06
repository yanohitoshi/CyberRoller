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
    ~GameClearEffect()override;

    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;

};

