#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

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
    CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor);

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
    GameObject* owner;
    ParticleState particleState;
    CrystalColor crystalColor;
    Vector3 tmpMovePos;
    int frameCount;
    int activeFrameCount;
    bool revers;
    float r;
    float yaw;
    const float yawSpeed = 0.06f;
};

