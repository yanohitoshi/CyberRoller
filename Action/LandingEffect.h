#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file LandingEffect.h
@brief LandingEffectの生成と更新を行う
*/
class LandingEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    LandingEffect(const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~LandingEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    // 親のGameObject保存用変数
    GameObject* owner;
    // 拡大縮小変数
    float mScale;
    // 透明度変数
    float mAlpha;

};

