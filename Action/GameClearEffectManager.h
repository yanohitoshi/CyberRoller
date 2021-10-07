#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file GameClearEffectManeger.h
@brief クリア時のエフェクトの生成を行う
*/
class GameClearEffectManager :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    GameClearEffectManager(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~GameClearEffectManager()override;
    
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

    /*
    @fn エフェクトを飛ばす方向計算処理関数
    @param _index何個目のエフェクトか
    @param _velocity 速度
    */
    void CalculatingDirectionProcess(int _index, Vector3& _velocity);
    
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
    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;
    // ランダムの範囲の割合
    const int RandValue;
    // 1度に生成するエフェクトの数
    const int MaxEffects;
    // 一回のエフェクトアクティブで生成ループを回す回数
    const int MaxGenerateCount;
    // 生成する頻度（フレームで比較）
    const int GenerateFrequency;

};

