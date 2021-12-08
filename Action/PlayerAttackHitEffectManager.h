#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerAttackHitEffectManager.h
@brief プレイヤーがエネミーへの攻撃を成功したときのエフェクトの生成を行うクラス
*/
class PlayerAttackHitEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    PlayerAttackHitEffectManager(PlayerObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerAttackHitEffectManager()override;

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
    void ActiveEffect();

    /*
    @fn エフェクト生産処理関数
    */
    void GenerateEffect();

    // 親のGameObject保存用変数
    PlayerObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // 生成するエフェクトのポジション
    Vector3 effectPosition;
    // ポジションを補正する値
    const float CorrectionPosition;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;
};

