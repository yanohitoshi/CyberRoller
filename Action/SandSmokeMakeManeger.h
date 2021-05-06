#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
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

    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // フレームカウント用変数
    int frameCount;
    // 親となる動く壁のサイズを見てどれくらいの幅でeffectを出すか決める用の変数
    Vector3 ownerSize;

    // 速度の最低値
    const Vector3 LowestVelValue;

    // ポジションXをずらす値
    const float ShiftPositionX;
    // 大きい壁の時のポジションYをずらす値
    const float MaxShiftPositionY;
    // 大きい壁の時のポジションYをずらす値
    const float MinShiftPositionY;
    // 大きい壁のサイズ
    const float BigWallSize;
    // 小さい壁のサイズ
    const float SmallWallSize;
    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;

    // ランダムの範囲の割合X
    const int RandValueX;
    // 大きい壁のランダムの範囲の割合Y
    const int BigRandValueY;
    // 小さい壁ランダムの範囲の割合Y
    const int SmallRandValueY;
    // ランダムの範囲の割合Z
    const int RandValueZ;
    // 生成する頻度（フレームで比較）
    const int GenerateFrequency;
    // 大きい壁の場合の1度に生成するエフェクトの数
    const int SmallWallMaxEffect;
    // 小さい壁の場合の1度に生成するエフェクトの数
    const int BigWallMaxEffect;
};

