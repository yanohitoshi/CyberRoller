#pragma once
#include "ParticleEffectBase.h"
class PlayerSandSmokeEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    @param  走り状態か判定フラグ
    */
    PlayerSandSmokeEffect(const Vector3& _pos, const Vector3& _velocity, bool _run);
    ~PlayerSandSmokeEffect()override;

    /*
    @fn 更新処理
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool runFlag;

};

