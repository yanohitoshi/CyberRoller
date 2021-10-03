#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file PlayerKnockBackEffect.h
@brief ノックバックエフェクトの更新を行うクラス
*/
class PlayerKnockBackEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    PlayerKnockBackEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _distance);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerKnockBackEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn 回転処理関数
    @brief	エフェクトの回転を行う
    */
    void RotateEffect();

    // 毎フレーム足すscale値 
    const float AddScale;
    // 毎フレーム引くalpha値
    const float SubAlpha;
    // ランダムな値の範囲
    const int RandValue;
    // エフェクトの色
    const Vector3 EffectColor;

};

