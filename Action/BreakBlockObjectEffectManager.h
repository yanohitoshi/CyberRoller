#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// クラスの前方宣言
class BreakBlockObject;

/*
@file BreakBlockObjectEffectManager.h
@brief 壊れるブロックのエフェクトの生成を行う
*/
class BreakBlockObjectEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    BreakBlockObjectEffectManager(BreakBlockObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~BreakBlockObjectEffectManager()override;

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
    @fn 土埃エフェクト生産処理関数
    */
    void GenerateDustEffectProcess();

    /*
    @fn 破片エフェクト生産処理関数
    */
    void GenerateDebrisEffectProcess();

    // 親のGameObject保存用変数
    BreakBlockObject* owner;

    // particleの状態管理用変数
    ParticleState particleState;

    // 2の倍数の時にフレームカウントと比較するための定数
    const int TowFrequency;
    // 3の倍数の時にフレームカウントと比較するための定数
    const int ThreeFrequency;

    // 埃エフェクトの最大数
    const int DustMaxEffect;
    // 埃用のランダムに用いる値
    const int DustEffectRandValue;

    // 破片エフェクトの最大数
    const int DebrisMaxEffect;
    // 破片用のランダムに用いる値
    const int DebrisEffectRandValue;

    // ランダムの値を作る際の補正値
    const float CorrectionRandValue;
    // ランダムの値に掛ける最後の補正値
    const float LastCorrection;
    // Activeになってからのカウントを数える
    int activeCount;
    // エフェクト本体に渡すポジション
    Vector3 effectPosition;
    // エフェクト本体に渡す速度
    Vector3 effectVelocity;
    // 1度だけ生成する用の生成フラグ変数
    bool generateEffectsFlag;
};