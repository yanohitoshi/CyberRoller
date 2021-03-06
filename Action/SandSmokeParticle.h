#pragma once

#include "ParticleEffectBase.h"

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
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;

};

