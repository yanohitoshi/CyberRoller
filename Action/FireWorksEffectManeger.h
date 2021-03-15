#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file FireWorksEffectManeger.h
@brief FireWorksEffectManegerの生成と更新を行う
*/
class FireWorksEffectManeger :
    public GameObject
{
public:
    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    FireWorksEffectManeger(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~FireWorksEffectManeger()override;
    
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
    // クリスタルeffectの色を管理する変数
    CrystalColor crystalColor;
    int frameCount;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;
    // 発生させたparticleの数を数える変数
    int particleCount;
};

