#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file FireWorksEffectManeger.h
@brief 花火エフェクトの生成を行う
*/
class FireWorksEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    FireWorksEffectManager(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~FireWorksEffectManager()override;
    
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
    @fn エフェクトの色と向きを設定する関数
    */
    void SelectEffectColorProcess(int _index,Vector3& _velocity);

    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // クリスタルeffectの色を管理する変数
    CrystalColor crystalColor;
    int frameCount;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;
    // 発生させたparticleの数を数える変数
    int particleCount;
    // ランダムな値を生成する際にかける補正
    const float CorrectionRandValue;
    // ランダムな値に対して最後にかける補正値
    const float LastCorrection;
    // ランダムの範囲の割合
    const int RandValue;
    // 1度に生成するエフェクトの数
    const int MaxEffects;

    // 2の倍数の時にフレームカウントと比較するための定数
    const int TowFrequency;
    // 4の倍数の時にフレームカウントと比較するための定数
    const int FourFrequency;
    // 6の倍数の時にフレームカウントと比較するための定数
    const int SixFrequency;
    // 8の倍数の時にフレームカウントと比較するための定数
    const int EightFrequency;
};

