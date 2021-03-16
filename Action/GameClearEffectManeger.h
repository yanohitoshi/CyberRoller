#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
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
    @param	_owner 親クラスのポインタ
    */
    GameClearEffectManeger(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~GameClearEffectManeger()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // フレームカウント用変数
    int frameCount;
    // 1度だけ生成する用の生成フラグ変数
    int generateCount;
    // 発生させたparticleの数を数える変数
    int particleCount;
};

