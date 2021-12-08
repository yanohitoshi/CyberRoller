#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class Mesh;

/*
@file DebrisEffectObject.h
@brief 破片エフェクトの更新を行う
*/
class DebrisEffectObject :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親となるクラスのポインタ
    @param	方向ベクトル
    */
    DebrisEffectObject(const Vector3& _pos, const Vector3& _direction);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~DebrisEffectObject()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn 生存時間のカウントダウン
    */
    void LifeCountDown();

    // Meshを管理するクラス
    Mesh* mesh;
    // 3Dモデルの描画を行うクラス
    MeshComponent* meshComponent;

    // 方組ベクトル
    Vector3 direction;
    // 生存時間
    int lifeCount;
    // 移動速度
    float moveSpeed;

    // 生存時間の最大値定数
    const int MaxLifeCount;
    // 速度に足す力
    const float MovePower;

    // ランダムな速度を得るための値
    const int SpeedRandValue;
    // ランダムな速度の最低値
    const int SpeedLowestValue;

    // ランダムな回転値を得るための値
    const int RotateRandValue;
    // ランダムな回転値の最低値
    const int RotateLowestValue;

    // 落下速度定数
    const float FallSpeed;
};

