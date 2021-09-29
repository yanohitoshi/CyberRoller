#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class EnemyObjectBase;

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

    // 親のGameObject保存用変数
    EnemyObjectBase* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // 1度に生成するエフェクトの数
    const int MaxEffects;
    // 1度に生成するエフェクトの数
    const int MaxExplosionEffects;
    // 1度だけ生成する用の生成フラグ変数
    bool generateExplosionEffectsFlag;
    int frameCount;

    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;
    const int RandValueX;
    const int RandValueY;
    const int RandValueZ;
};

