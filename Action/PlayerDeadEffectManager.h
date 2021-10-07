#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerDeadEffectManager.h
@brief 死亡エフェクトの生成を行うクラス
*/
class PlayerDeadEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    PlayerDeadEffectManager(PlayerObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerDeadEffectManager()override;

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
    // エフェクトの位置をプレイヤーの体に合わせるための間隔
    Vector3 distance;
    // エフェクトの位置をプレイヤーの体に合わせるための間隔を計算するためのオフセット定数
    const float DistanceOffset;
    // 死亡状態になってからの時間を数える
    int generationCount;
    // エフェクトを発生させ始める時間
    const int GenerationTime;
    // エフェクトを生成する時間を数える
    int effectFrameCount;
    // ポジションをずらすためのオフセット
    const float PositionOffset;
    // z軸を少しずらすための定数
    const float ShiftPositionZ;
};

