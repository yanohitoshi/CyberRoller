#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// クラスの前方宣言
class CollectionObject;
enum CrystalColor;

/*
@file CollectionEffectManager.h
@brief 収集物エフェクトの生成を行う
*/
class CollectionEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    */
    CollectionEffectManager(CollectionObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CollectionEffectManager()override;

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
    @fn 波紋エフェクト生産処理関数
    */
    void CreationRipplesEffect();

    /*
    @fn 光エフェクト生産処理関数
    */
    void CreationLightEffect();

    // 生成フラグ
    bool generateFlag;

    // 親クラスのポインタ変数
    CollectionObject* owner;
    // 生成するエフェクトのポジション
    Vector3 effectPosition;
    // particleの状態管理用変数
    ParticleState particleState;
    // Activeの時間を数える
    int activeCount;
    // 色番号変数
    int colorNum;

    // エフェクトがActiveな時間
    const int ActiveTime;
    // ランダムの値定数
    const int RandValue;
    // ランダムの範囲の割合
    const int LightEffectRandValue;
    // 1度に生成するエフェクトの数
    const int MaxLightEffects;
    // 2の倍数の時にフレームカウントと比較するための定数
    const int TowFrequency;
    // 3の倍数の時にフレームカウントと比較するための定数
    const int ThreeFrequency;

};

