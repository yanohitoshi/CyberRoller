#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file PlayerAttackHitEffect.h
@brief プレイヤーがエネミーへの攻撃を成功したときのエフェクトの更新を行うクラス
*/
class PlayerAttackHitEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    PlayerAttackHitEffect(GameObject* _owner,const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerAttackHitEffect()override;

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

