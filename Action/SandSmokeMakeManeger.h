#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"
class SandSmokeMakeManeger :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    SandSmokeMakeManeger(GameObject* _owner);
    ~SandSmokeMakeManeger()override;
    
    /*
    @fn 更新処理
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    Vector3 ownerSize;
};

