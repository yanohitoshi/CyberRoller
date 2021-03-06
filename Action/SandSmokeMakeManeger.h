#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file SandSmokeMakeManeger.h
@brief SandSmokeMakeManegerの生成と更新を行う
*/
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
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    Vector3 ownerSize;
};

