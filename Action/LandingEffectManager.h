#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file LandingEffectManeger.h
@brief 着地時の土煙の生成を行う
*/
class LandingEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    LandingEffectManager(PlayerObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~LandingEffectManager()override;
    
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
    PlayerObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // 1度だけ生成する用の生成フラグ変数
    bool generateEffectsFlag;
    // 1度に生成するエフェクトの数
    const int MaxEffects;
};