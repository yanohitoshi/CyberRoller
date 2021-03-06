#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file GameClearEffectManeger.h
@brief GameClearEffectManegerの生成と更新を行う
*/
class GameClearEffectManeger :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    GameClearEffectManeger(GameObject* _owner);
    ~GameClearEffectManeger()override;
    
    /*
    @fn 更新処理
    @param	最後のフレームを完了するのに要した時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    int generateCount;
    int particleCount;
};

