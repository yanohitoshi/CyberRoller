#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class Animation;
enum class TitlePlayerState;

///*
//@enum AnimState
//    　プレイヤーのアニメーションの状態
//      タイトル用
//*/
//enum TitlePlayerState
//{
//    // アイドリング状態
//    IDLE,
//    // 走り状態
//    RUN,
//    // ジャンプループ
//    JUMPLOOP,
//    // ジャンプ開始
//    JUMPSTART,
//    // ジャンプ終了
//    JUMPEND,
//    // ジャンプアタック
//    JUMPATTACK,
//    // 総ステータス数
//    ITEMNUM
//};

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
    
    /*
    @fn 回転処理関数
    */
    void RotationProcess(float _angle,Vector3 _axis);
    
private:


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

    // 全stateが格納されるマップ
    std::unordered_map<TitlePlayerState, TitlePlayerStateBase*> statePoolMap;

    //3Dモデルの描画を行うクラス
    SkeletalMeshComponent* skeltalMeshComponent;
    // Meshの読み込みを行うクラス
    Mesh* mesh;
    // 3Dモデルの描画を行うクラス
    MeshComponent* meshComponent;

    // 重力定数
    const float Gravity;
    // 接地フラグ
    bool onGround;
    // ジャンプフラグ
    bool jumpFlag;
    // ジャンプの間隔を測るためのカウント
    int jumpDelayCount;
    // ジャンプした回数
    int jumpCount;
    // 作用するジャンプ力
    float jumpPower;
    // 初速
    const float FirstJumpPower;
    // ジャンプする時間用カウント
    float jumpFrameCount;
    float jumpAttackRotationAngle;

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

    // 回転角定数
    const float JumpAttackRotationAngle;

public:

    /*
    @fn skeltalMeshComponentのgetter関数
    @return SkeletalMeshComponent　SkeletalMeshComponentクラスのポインタを返す
    */
    SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

    /*
    @fn meshComponentのgetter関数
    @return meshComponent　meshComponentクラスのポインタを返す
    */
    MeshComponent* GetMeshComponent() { return meshComponent; }

    /*
    @fn Animationのgetter関数
    @param _state 現在のプレイヤーのステータス
    @return Animation Animationクラスのポインタを返す
    */
    const Animation* GetAnimation(TitlePlayerState _state);

    bool GetJumpFlag() { return jumpFlag; }
    bool GetOnGroundFlag() { return onGround; }
    int GetJumpFrameCount() { return jumpFrameCount; }
    int GetJumpCount() { return jumpCount; }
    float GetJumpPower() { return jumpPower; }

    void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
    void SetOnGround(bool _onGround) { onGround = _onGround; }
    void SetJumpFrameCount(int _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
    void SetJumpCount(int _jumpCount) { jumpCount = _jumpCount; }
    void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }
};

