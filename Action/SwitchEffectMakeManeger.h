#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file SwitchEffectMakeManeger.h
@brief スイッチのエフェクトの生成を行う
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
    @fn エフェクトがアクティブ時の処理関数
    */
    void ActiveEffectProcess();

    /*
    @fn エフェクトを飛ばす方向計算処理関数
    */
    void CalculatingDirectionProcess(int _index, Vector3& _velocity);

    // 親のGameObject保存用変数
    GameObject* owner;

    // particleの状態管理用変数
    ParticleState particleState;

    // switchがONになったかどうかフラグ
    bool checkOnFlag;
    // 前のフレームのスイッチの状態を保存する用フラグ変数
    bool tmpCheckOnFlag;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;

    // ランダムの範囲の割合
    const int RandValue;
    // 1度に生成するエフェクトの数
    const int MaxEffects;

    // Z軸のみに適応させる補正値
    const float SecondCorrectionValue;
    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;

    // 2の倍数の時にフレームカウントと比較するための定数
    const int TowFrequency;
    // 3の倍数の時にフレームカウントと比較するための定数
    const int ThreeFrequency;
    // 4の倍数の時にフレームカウントと比較するための定数
    const int FourFrequency;
    // 6の倍数の時にフレームカウントと比較するための定数
    const int SixFrequency;
};

