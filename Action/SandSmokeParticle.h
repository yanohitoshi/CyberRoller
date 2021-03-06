#pragma once

#include "ParticleEffectBase.h"
/*
@file SandSmokeParticle.h
@brief SandSmokeParticleの生成と更新を行う
*/
class SandSmokeParticle :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    SandSmokeParticle(const Vector3& _pos, const Vector3& _velocity);
    ~SandSmokeParticle()override;
    
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

