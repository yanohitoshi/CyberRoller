#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file SwitchEffectMakeManeger.h
@brief SwitchEffectMakeManegerの生成と更新を行う
*/
class SwitchEffectMakeManeger :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    SwitchEffectMakeManeger(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~SwitchEffectMakeManeger()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn エフェクトの生成関数
    */
    void CreateEffect();

    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // switchがONになったかどうかフラグ
    bool ChackOnFlag;
    // 前のフレームのスイッチの状態を保存する用フラグ変数
    bool tmpChackOnFlag;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;
    // ランダムの範囲の割合
    const int RandValue;
    // Z軸のみに適応させる補正値
    const float SecondCorrectionValue;
    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;
    // 1度に生成するエフェクトの数
    const int MaxEffects;


};

