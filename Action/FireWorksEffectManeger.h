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
    @param	親クラスのポインタ
    */
    FireWorksEffectManeger(GameObject* _owner);
    ~FireWorksEffectManeger()override;
    
    /*
    @fn 更新処理
    @param	最後のフレームを完了するのに要した時間
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

