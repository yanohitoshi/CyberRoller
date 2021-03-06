#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file LandingEffectManeger.h
@brief LandingEffectManegerの生成と更新を行う
*/
class LandingEffectManeger :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    LandingEffectManeger(GameObject* _owner);
    ~LandingEffectManeger()override;
    
    /*
    @fn 更新処理
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    float tmpVelZ;
    bool generateFlag;

};

