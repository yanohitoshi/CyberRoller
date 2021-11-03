#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class BreakBlockObject;

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
    @fn エフェクト生産処理関数
    */
    void GenerateEffectProcess();

    /*
    @fn 爆発エフェクト生産処理関数
    */
    void GenerateExplosionEffectProcess();

    // 親のGameObject保存用変数
    BreakBlockObject* owner;

    // particleの状態管理用変数
    ParticleState particleState;

    Vector3 effectPosition;
    Vector3 effectVelocity;
    // 1度だけ生成する用の生成フラグ変数
    bool generateExplosionEffectsFlag;
};

