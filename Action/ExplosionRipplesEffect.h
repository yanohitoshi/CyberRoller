#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file ExplosionRipplesEffect.h
@brief 爆発の波紋エフェクトの更新を行う
*/
class ExplosionRipplesEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	親となるクラスのポインタ
    @param	ポジション
    */
    ExplosionRipplesEffect(GameObject* _owner, const Vector3& _pos);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ExplosionRipplesEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn エフェクトの回転処理
    */
    void RotateEffect();

    // 角度
    float angle;

    const int RandValue;
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
    // ランダムな速度の最低値
    const int RotateLowestValue;
    // Y軸の回転角度
    const float AxisYAngle;
};

