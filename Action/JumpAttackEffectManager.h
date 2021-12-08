#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file JumpAttackEffectManager.h
@brief ジャンプ攻撃中のエフェクトの生成を行うクラス
*/
class JumpAttackEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    JumpAttackEffectManager(GameObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~JumpAttackEffectManager()override;

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
    void ActiveEffect();

    /*
    @fn エフェクト生産処理関数
    */
    void GenerateEffect();

    // 親のGameObject保存用変数
    GameObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // 生成するエフェクトのポジション
    Vector3 effectPosition;
};

