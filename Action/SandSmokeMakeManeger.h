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

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~SandSmokeMakeManeger()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    Vector3 ownerSize;
};

