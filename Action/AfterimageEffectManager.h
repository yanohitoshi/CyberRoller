#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class AfterimageEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    AfterimageEffectManager(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~AfterimageEffectManager()override;

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
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // 生成するエフェクトのポジション
    Vector3 effectPosition;
    // 一度に生成するエフェクトの最大数
    const int MaxEffects;
    // ランダムの範囲の割合
    const int RandValue;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;
};

