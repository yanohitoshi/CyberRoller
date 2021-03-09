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

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~SwitchEffectMakeManeger()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

