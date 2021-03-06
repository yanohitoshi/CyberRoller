#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

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
    @param	フレームレート固定用deltaTime
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

