#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// クラスの前方宣言
class EnemyObjectBase;

/*
@file EnemyDeadEffectManager.h
@brief エネミーの死亡時のエフェクトの生成を行うクラス
*/
class EnemyDeadEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    EnemyDeadEffectManager(EnemyObjectBase* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~EnemyDeadEffectManager()override;

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
    @fn エフェクト生産処理関数
    */
    void GenerateEffectProcess();

    /*
    @fn 爆発エフェクト生産処理関数
    */
    void GenerateExplosionEffectProcess();

    // 親のGameObject保存用変数
    EnemyObjectBase* owner;

    // particleの状態管理用変数
    ParticleState particleState;

    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;

    // 1度に生成する爆発エフェクトの数
    const int MaxExplosionEffects;
    // 爆発エフェクトが発生するまでの待機時間
    const int WaitingExplosionTime;
    // ランダムの範囲
    const int RandValue;

    // 1度だけ生成する用の生成フラグ変数
    bool generateExplosionEffectsFlag;
    // エフェクトが有効化されてからのフレームを測る
    int effectFrameCount;

};

