#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerSandSmokeMakeManeger.h
@brief PlayerSandSmokeMakeManegerの生成と更新を行う
*/
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
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    Vector3 effectPosition;
    int frameCount;
    int generateCount;

};

