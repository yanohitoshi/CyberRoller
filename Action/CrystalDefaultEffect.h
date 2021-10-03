#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file CrystalDefaultEffect.h
@brief クリスタルのエフェクトの更新を行う
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

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CrystalDefaultEffect()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn フェードイン関数
    */
    void FadeInProcess();

    // フェードインフラグ変数
    bool inFlag;

    // alpha値の最大値
    const float MaxAlphaValue;

    // 毎フレーム足すscale値 
    const float AddScale;
    // 毎フレーム足すAlpha値
    const float AddAlpha;
    // 毎フレーム引くAlpha値
    const float SubAlpha;
};

