#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

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
    @param	フレームレート固定用deltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    int generateCount;
    int particleCount;
};

