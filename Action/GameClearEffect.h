#pragma once

#include "ParticleEffectBase.h"

/*
@file GameClearEffect.h
@brief GameClearEffectの生成と更新を行う
*/
class GameClearEffect
	: public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    GameClearEffect(const Vector3& _pos, const Vector3& _velocity);
    ~GameClearEffect()override;

    /*
    @fn 更新処理
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;

};

