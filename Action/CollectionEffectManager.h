#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

enum CrystalColor;
class CollectionObject;

class CollectionEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親クラスのポインタ
    @param	何色か判定用Tag
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
    void ActiveEffectProcess(float _deltaTime);

    /*
    @fn エフェクト生産処理関数
    */
    void GenerateEffectProcess();

    /*
    @fn 波紋エフェクト生産処理関数
    */
    void CreationRipplesEffect();

    void CreationLightEffect();


    CollectionObject* owner;
    bool generateFlag;
    Vector3 effectPosition;
    // particleの状態管理用変数
    ParticleState particleState;
    int activeCount;
    int colorNum;
    // ランダムの範囲の割合
    const int LightEffectRandValue;
    // 1度に生成するエフェクトの数
    const int MaxLightEffects;

};

