#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file LandingEffectManeger.h
@brief LandingEffectManegerの生成と更新を行う
*/
class LandingEffectManeger :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    LandingEffectManeger(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~LandingEffectManeger()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn エフェクトがアクティブ時の処理関数
    */
    void ActiveEffectProcess();

    /*
    @fn エフェクトを飛ばす方向計算処理関数
    */
    void CalculatingDirectionProcess(int _index, Vector3& _velocity);

    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // プレイヤーのZ軸の移動量を保存するための変数
    float tmpVelZ;
    // 1度に生成するエフェクトの数
    const int MaxEffects;
};

