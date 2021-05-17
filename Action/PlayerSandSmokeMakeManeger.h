#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerSandSmokeMakeManeger.h
@brief PlayerSandSmokeMakeManegerの生成と更新を行う
*/
class PlayerSandSmokeMakeManeger :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    PlayerSandSmokeMakeManeger(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerSandSmokeMakeManeger()override;

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
    
    /*
    @fn エフェクトのポジションを右にずらす関数
    */
    void ShiftRightEffectPosition();

    /*
    @fn エフェクトのポジションを左にずらす関数
    */
    void ShiftLeftEffectPosition();

    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // アニメーションに合わせて土煙の位置をずらす用のポジション変数
    Vector3 effectPosition;
    // フレームカウント用変数
    int frameCount;
    // 生成した数を数えるためのカウント
    int generateCount;
    // ownerの速度が一定以上の場合に生成するための定数
    const float GenerateSpeedValue;
    // 足元から出ているように見せるためにずらす値
    const float ShiftPositionValue;

};

