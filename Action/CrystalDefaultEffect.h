#pragma once
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file CrystalDefaultEffect.h
@brief CrystalDefaultEffectの生成と更新を行う
*/
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
    
    /*
    @fn 更新処理
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool inFlag;
};

