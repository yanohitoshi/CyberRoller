#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerKnockBackEffectManager.h
@brief ノックバックエフェクトの生成を行うクラス
*/
class PlayerKnockBackEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    PlayerKnockBackEffectManager(PlayerObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerKnockBackEffectManager()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn エフェクトがアクティブ時の処理関数
    */
    void ActiveEffectProcess();

    /*
    @fn エフェクト生産処理関数
    */
    void GenerateEffectProcess();

    // 親のGameObject保存用変数
    PlayerObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // 間隔
    Vector3 distance;
    // エフェクトを生成する時間を数える
    int effectFrameCount;
    // ポジションをずらすためのオフセット
    const float PositionOffset;
};

