#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"
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
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    float tmpVelZ;
    bool generateFlag;

};

