#pragma once
#include "ParticleEffectBase.h"

/*
@file LandingEffect.h
@brief LandingEffectの生成と更新を行う
*/
class LandingEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    LandingEffect(const Vector3& _pos, const Vector3& _velocity);
    ~LandingEffect()override;

    /*
    @fn 更新処理
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    ParticleState particleState;
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

