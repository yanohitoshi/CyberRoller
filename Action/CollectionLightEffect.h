#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

// クラスの前方宣言
enum CrystalColor;

/*
@file CollectionLightEffect.h
@brief 光エフェクトの更新を行う
*/
class CollectionLightEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	親となるクラスのポインタ
    @param	ポジション
    @param	移動速度
    */
    CollectionLightEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _direction,CrystalColor _crystalColor);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CollectionLightEffect()override;

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
    // 方向ベクトル
    Vector3 direction;
    // サイン関数に渡す値
    float value;
    // サイン関数に足す値 
    const float AddValue;
    // サイン関数から返ってきた値
    float sinV;
    // alpha値の初期値
    const float InitAlpha;
    // scale値の初期値
    const float InitScale;

    // ランダムな速度を得るための定数
    const int SpeedRandValue;
    // ランダムな速度の最低値
    const int SpeedLowestValue;
    // ランダムなSin関数に渡す値を得るための定数
    const int SinRandValue;
};

