#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SkeletalMeshComponent;
class Animation;

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

};

