#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

class MoveWallBlock;

/*
@enum クリスタル用effectの色のTag
*/
enum CrystalColor
{
    WHITE,
    RED,
    BLUE,
    GREEN,
};

/*
@file CrystalEffectManager.h
@brief CrystalEffectManagerの生成と更新を行う
*/
class CrystalEffectManager :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    @param	何色か判定用Tag
    */
    CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor, MoveWallBlock* _lastMoveWall);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CrystalEffectManager()override;
    
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
    @fn ポジションの回転処理関数
    */
    void RotationProcess(float _deltaTime);

    MoveWallBlock* lastMoveWallBlock;

    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // クリスタルeffectの色を管理する変数
    CrystalColor crystalColor;
    // 回転させる際の一時保存用変数
    Vector3 tmpMovePos;
    // フレームカウント用変数
    int frameCount;
    // effectを発生させるタイミングを測るカウント変数
    int activeFrameCount;
    // effectを発生させるかどうか
    bool isEffectActive;
    // 回転の半径変数
    const float Radius;
    // 回転で用いるヨーの角度変数
    float yaw;
    // 回転速度
    const float YawSpeed;
    // Z軸のポジションをずらす値
    const float ShiftPositionZ;
    // Z軸のみに適応させる補正値
    const float SecondCorrectionValue;
    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;
    // ランダムの範囲の割合
    const int RandValue;
    // デルタタイムにかける補正
    const float DeltaTimeCorrectionValue;

};

