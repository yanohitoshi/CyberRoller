#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// クラスの前方宣言
class MoveWallBlock;

/*
@enum クリスタル用effectの色のTag
*/
enum CrystalColor
{
    // 白色
    WHITE = 0,
    // 赤色
    RED = 1,
    // 青色
    BLUE = 2,
    // 緑色
    GREEN = 3,
    // 無
    NONE = 4
};

/*
@file CrystalEffectManager.h
@brief クリスタルのエフェクトの生成を行う
*/
class CrystalEffectManager :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    @param	何色か判定用Tag
    @param シーン最後の動く壁のポインタ
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
    @param	_deltaTime 前のフレームでかかった時間
    */
    void ActiveEffect(float _deltaTime);
    
    /*
    @fn エフェクト生産処理関数
    */
    void GenerateEffect();
    
    /* 
    @fn ポジションの回転処理関数
    @param	_deltaTime 前のフレームでかかった時間
    */
    void RotationProcess(float _deltaTime);

    // ステージ最後の壁の情報を得るためのポインタ
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
    // 8の倍数の時にフレームカウントと比較するための定数
    const int EightFrequency;
};

