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

    GameObject* owner;
    ParticleState particleState;
    CrystalColor crystalColor;
    int frameCount;
    bool generateFlag;
    int particleCount;
};

