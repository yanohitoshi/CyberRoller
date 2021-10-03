#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

// クラスの前方宣言
class EnemyObjectBase;

/*
@file EnemyElectricShockEffect.h
@brief 電撃エフェクトの更新を行うクラス
*/
class EnemyElectricShockEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    EnemyElectricShockEffect(GameObject* _owner,const Vector3& _pos);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~EnemyElectricShockEffect()override;

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

