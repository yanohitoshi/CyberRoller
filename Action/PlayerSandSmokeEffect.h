#pragma once
#include "ParticleEffectBase.h"

/*
@file PlayerSandSmokeEffect.h
@brief PlayerSandSmokeEffectの生成と更新を行う
*/
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

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerSandSmokeEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool runFlag;

};

