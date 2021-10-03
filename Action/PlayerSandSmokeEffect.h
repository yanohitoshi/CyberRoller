#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file PlayerSandSmokeEffect.h
@brief プレイヤーの土煙(走り)の更新を行う
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
    PlayerSandSmokeEffect(const Vector3& _pos, const Vector3& _velocity);

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
    
    // 毎フレーム足すscale値 
    const float AddScale;
    // 毎フレーム引くalpha値
    const float SubAlpha;
};

