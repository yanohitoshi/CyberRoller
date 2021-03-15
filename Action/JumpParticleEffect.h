#pragma once
#include "ParticleEffectBase.h"

/*
@file JumpParticleEffect.h
@brief JumpParticleEffectの生成と更新を行う
*/
class JumpParticleEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    JumpParticleEffect(const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~JumpParticleEffect()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    // particleのステータス管理用変数
    ParticleState particleState;
    // 親のGameObject保存用変数
    GameObject* owner;
    // 拡大縮小変数
    float mScale;
    // 透明度変数
    float mAlpha;

};

