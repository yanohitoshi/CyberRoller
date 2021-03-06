#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"

class PlayerSandSmokeMakeManeger :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    PlayerSandSmokeMakeManeger(GameObject* _owner);
    ~PlayerSandSmokeMakeManeger()override;

    /*
    @fn 更新処理
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    Vector3 effectPosition;
    int frameCount;
    int generateCount;

};

