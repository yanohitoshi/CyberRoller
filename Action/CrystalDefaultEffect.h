#pragma once
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

class CrystalDefaultEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    @param	何色か判定用Tag
    */
    CrystalDefaultEffect(const Vector3& _pos, const Vector3& _velocity,CrystalColor _crystalColor);
    ~CrystalDefaultEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool inFlag;
};

