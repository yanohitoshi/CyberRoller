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
    @param	_owner 親クラスのポインタ
    */
    PlayerSandSmokeMakeManeger(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerSandSmokeMakeManeger()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    Vector3 effectPosition;
    int frameCount;
    int generateCount;

};

