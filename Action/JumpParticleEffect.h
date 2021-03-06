#pragma once
#include "ParticleEffectBase.h"

/*
@file JumpParticleEffect.h
@brief JumpParticleEffectの生成と更新を行う
*/
class JumpParticleEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    JumpParticleEffect(const Vector3& _pos, const Vector3& _velocity);
    ~JumpParticleEffect()override;
    
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

