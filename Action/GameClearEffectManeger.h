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
    // 生成したループの回数をカウントする用の生成カウント変数
    int generateCount;
    // 生成を開始する高さ
    const float GenerateHeight;
    // ランダムの値を補正する値
    const float SecondCorrectionValue;
    // そのまま扱うと値が大きくなりすぎるので補正をかけるための値
    const float CorrectionRandValue;
    // ランダムの範囲の割合
    const int RandValue;
    // 1度に生成するエフェクトの数
    const int MaxEffects;
    // 一回のエフェクトアクティブで生成ループを回す回数
    const int MaxGenerateCount;
    // 生成する頻度（フレームで比較）
    const int GenerateFrequency;

};

