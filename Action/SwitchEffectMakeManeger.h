#pragma once
#include "GameObject.h"

#include "ParticleEffectBase.h"
/*
@file SwitchEffectMakeManeger.h
@brief SwitchEffectMakeManegerの生成と更新を行う
*/
class SwitchEffectMakeManeger :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    SwitchEffectMakeManeger(GameObject* _owner);
    ~SwitchEffectMakeManeger()override;
    
    /*
    @fn 更新処理
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

