#pragma once
#include "GameObject.h"

#include "ParticleEffectBase.h"

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
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

