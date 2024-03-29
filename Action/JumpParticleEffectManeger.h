#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file JumpParticleEffectManeger.h
@brief JumpParticleEffectManegerの生成と更新を行う
*/
class JumpParticleEffectManeger :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    JumpParticleEffectManeger(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~JumpParticleEffectManeger()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // プレイヤーのZ軸の移動量を保存するための変数
    float tmpVelZ;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;

};

