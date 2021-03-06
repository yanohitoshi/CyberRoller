#pragma once

#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

class FierWorksEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    @param	何色か判定用Tag
    */
    FierWorksEffect(const Vector3& _pos, const Vector3& _velocity , CrystalColor _crystalColor);
    ~FierWorksEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    bool inFlag;
    float mScale;
    float mAlpha;
    float speed;
};

