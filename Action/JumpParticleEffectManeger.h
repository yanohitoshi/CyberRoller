#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class JumpParticleEffectManeger :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    JumpParticleEffectManeger(GameObject* _owner);
    ~JumpParticleEffectManeger()override;
    
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

