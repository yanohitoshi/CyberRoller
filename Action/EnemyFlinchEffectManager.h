#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// クラスの前方宣言
class EnemyObjectBase;

/*
@file EnemyFlinchEffectManager.h
@brief エネミーの怯み時のエフェクトの生成を行うクラス
*/
class EnemyFlinchEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    EnemyFlinchEffectManager(EnemyObjectBase* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~EnemyFlinchEffectManager()override;

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
    EnemyObjectBase* owner;

    // particleの状態管理用変数
    ParticleState particleState;

    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;

    // 1度に生成する爆発エフェクトの数
    const int MaxExplosionEffects;
    // ランダムの範囲
    const int RandValue;

    // エフェクトが有効化されてからのフレームを測る
    int effectFrameCount;
    // 5の倍数の時にフレームカウントと比較するための定数
    const int FiveFrequency;
};

