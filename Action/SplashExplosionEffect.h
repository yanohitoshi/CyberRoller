#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file SplashExplosionEffect.h
@brief 爆発の飛沫エフェクトの更新を行う
*/
class SplashExplosionEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	親となるクラスのポインタ
    @param	ポジション
    @param	移動速度
    */
    SplashExplosionEffect(const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~SplashExplosionEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 毎フレーム足すscale値 
    const float AddScale;
    // 毎フレーム引くalpha値
    const float SubAlpha;
    // エフェクトの色
    const Vector3 EffectColor;
    // alpha値の初期値
    const float InitAlpha;
    // scale値の初期値
    const float InitScale;

    // ランダムな速度を得るための値
    const int SpeedRandValue;
    // ランダムな速度の補正値
    const int SpeedCorrection;
};

