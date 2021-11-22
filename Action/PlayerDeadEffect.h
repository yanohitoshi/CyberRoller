#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file PlayerDeadEffect.h
@brief 死亡エフェクトの更新を行うクラス
*/
class PlayerDeadEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	親となるクラスのポインタ
    @param	ポジション
    @param	プレイヤーの体に位置を合わせるための間隔
    */
    PlayerDeadEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _distance);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerDeadEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn エフェクトの回転処理関数
    @brief	エフェクトの回転を行う
    */
    void RotateEffect();

    /*
    @fn 回転計算処理
    @param _axis 回転軸
    */
    void Rotation(const Vector3 _axis);

    // 毎フレーム足すscale値 
    const float AddScale;
    // 毎フレーム引くalpha値
    const float SubAlpha;
    // ランダムな値の範囲
    const int RandValue;
    // エフェクトの色
    const Vector3 EffectColor;

    // alpha値の初期値
    const float InitAlpha;
    // scale値の初期値
    const float InitScale;
    // 移動速度定数
    const float MoveSpeed;
};

