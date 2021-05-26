#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SkeletalMeshComponent;
class Animation;

/*
@enum AnimState
    　プレイヤーのアニメーションの状態
      タイトル用
*/
enum TitleAnimState
{
    IDLE,
    WALK,
    RUN,
    JUMPLOOP,
    JUMPSTART,
    JUMPEND,
    DOWN,
    DOWN_LOOP,
    DOWN_UP,
    DOWN_OVER,
    PLAYER_DEAD,
    ITEMNUM
};

/*
@file TitlePlayerObject.h
@brief タイトルシーン中でのプレイヤー
       ただアニメーションを再生するだけのクラス
*/
class TitlePlayerObject :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	再利用するかフラグ
    @param	オブジェクト判別用tag
    */
    TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TitlePlayerObject()override;
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;
    
private:

    /*
    @fn 回転処理関数
    */
    void RotationProcess();

    /*
    @fn 重力処理関数
    @param	_deltaTime 前のフレームでかかった時間
    */
    void GravityProcess(float _deltaTime);

    /*
    @fn ジャンプディレイ処理関数
    */
    void JumpDelayProcess();

    /*
    @fn ジャンプ処理関数
    */
    void JumpProcess();

    /*
    @fn 接地判定処理関数
    */
    void IsGroundingProcess();

    /*
    @fn アニメーションの更新処理
    */
    void AnimationUpdate();

    // アニメーション用vector配列
    std::vector<const Animation*> animTypes;
    // アニメーションの状態用変数
    int animState;

    //3Dモデルの描画を行うクラス
    SkeletalMeshComponent* skeltalMeshComponent;
    
    // 重力定数
    const float Gravity;
    // 接地フラグ
    bool onGround;
    // ジャンプフラグ
    bool jumpFlag;
    // ジャンプの間隔を測るためのカウント
    int jumpDelayCount;
    // 作用するジャンプ力
    float jumpPower;
    // 初速
    float firstJumpPower;
    // ジャンプする時間用カウント
    float jumpFrameCount;

    // 落下速度の最大値
    const float MaxFallSpeed;

    // ジャンプを続けるフレームカウント定数
    const float JumpLimitTime;

    // ジャンプする間隔の時間定数
    const int JumpDelayTime;

    // ジャンプ加速度定数
    const float JumpSpeed;

    // 接地判定を取る座標値定数
    const float OnGroundCoordinate;

    // 回転角定数
    const float RotationAngle;

};

