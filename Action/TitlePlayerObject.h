#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SkeletalMeshComponent;
class Mesh;
class Animation;
class TitleJumpAttackPlayerObject;
class TitlePlayerStateBase;
enum class TitlePlayerState;

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
    @brief ステートプール用マップにステートクラスを追加する関数
    @param	_state 追加するステートクラスのポインタ
    @param	_stateTag 鍵となるタグ
    */
    void AddStatePoolMap(TitlePlayerStateBase* _state, TitlePlayerState _stateTag);

    /*
    @brief ステートプール用マップからステートクラスを削除する関数
    @param	_stateTag 鍵となるタグ
    */
    void RemoveStatePoolMap(TitlePlayerState _stateTag);

    /*
    @brief ステートプール用マップをクリアする
    */
    void ClearStatePoolMap();

    //3Dモデルの描画を行うクラス
    SkeletalMeshComponent* skeltalMeshComponent;
    // Meshの読み込みを行うクラス
    Mesh* mesh;
    // アニメーション用vector配列
    std::vector<const Animation*> animTypes;

    // 今のプレーヤーのstate状態を保存するための変数
    TitlePlayerState nowState;
    // 変更された次のプレーヤーのstate状態を保存するための変数
    TitlePlayerState nextState;

    // 全stateが格納されるマップ
    std::unordered_map<TitlePlayerState, TitlePlayerStateBase*> statePoolMap;

    // ジャンプアタック状態のプレイヤークラスのポインタ
    TitleJumpAttackPlayerObject* titleJumpAttackPlayerObject;

    // 初期ポジション定数
    const Vector3 InitPosition;
    // ジャンプフラグ
    bool jumpFlag;
    // ジャンプの間隔を測るためのカウント
    int jumpDelayCount;
    // ジャンプした回数
    int jumpCount;
    // 作用するジャンプ力
    float jumpPower;
    // ジャンプする時間用カウント
    int jumpFrameCount;

    // 回転角定数
    const float RotationAngle;

public:

    /*
    @fn skeltalMeshComponentのgetter関数
    @return SkeletalMeshComponent　SkeletalMeshComponentクラスのポインタを返す
    */
    SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

    /*
    @fn titleJumpAttackPlayerObjectのgetter関数
    @return titleJumpAttackPlayerObject　titleJumpAttackPlayerObjectクラスのポインタを返す
    */
    TitleJumpAttackPlayerObject* GetTitleJumpAttackPlayerObject() { return titleJumpAttackPlayerObject; }

    /*
    @fn Animationのgetter関数
    @param _state 現在のプレイヤーのステータス
    @return Animation Animationクラスのポインタを返す
    */
    const Animation* GetAnimation(TitlePlayerState _state);

    /*
    @fn InitPositionのgetter関数
    @return InitPosition　InitPositionを返す
    */
    Vector3 GetInitPosition() { return InitPosition; }

    /*
    @fn jumpFlagのgetter関数
    @return jumpFlag　jumpFlagを返す
    */
    bool GetJumpFlag() { return jumpFlag; }

    /*
    @fn jumpFrameCountのgetter関数
    @return jumpFrameCount　jumpFrameCountを返す
    */
    int GetJumpFrameCount() { return jumpFrameCount; }

    /*
    @fn jumpCountのgetter関数
    @return jumpCount　jumpCountを返す
    */
    int GetJumpCount() { return jumpCount; }

    /*
    @fn jumpPowerのgetter関数
    @return jumpPower　jumpPowerを返す
    */
    float GetJumpPower() { return jumpPower; }

    /*
    @fn jumpFlagのsetter関数
    @param	bool _jumpFlag true:ジャンプ中 false:ジャンプ中でない
    */
    void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
    
    /*
    @fn jumpFrameCountのsetter関数
    @param	int _jumpFrameCount ジャンプ中のカウント
    */
    void SetJumpFrameCount(int _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
    
    /*
    @fn nextStateのsetter関数
    @param	int _jumpCount ジャンプした回数
    */
    void SetJumpCount(int _jumpCount) { jumpCount = _jumpCount; }
    
    /*
    @fn nextStateのsetter関数
    @param	float _jumpPower ジャンプ力
    */
    void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }
};

