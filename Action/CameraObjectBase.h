#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class CameraObjectStateBase;
enum class CameraState;

/*
@file CameraObjectBase.h
@brief GameObjectを継承したカメラの基底クラス
*/
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @fn コンストラクタ
    @param	再利用するかフラグ
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CameraObjectBase();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    virtual void UpdateGameObject(float _deltaTime = 1.0f);

    /*
    @fn 入力関数
    @brief	入力処理を行う
    @param	_keyState 入力情報
    */
    virtual void GameObjectInput(const InputState& _keyState);

    /*
    @brief リスポーンしたときにカメラの位置を初期状態にセットする関数
    */
    void ResetCamera() { yaw = Math::ToRadians(180); pitch = Math::ToRadians(30); }

    /*
    @brief ステートプール用マップにステートクラスを追加する関数
    @param	_state 追加するステートクラスのポインタ
    @param	_stateTag 鍵となるタグ
    */
    void AddStatePoolMap(CameraObjectStateBase* _state, CameraState _stateTag);

    /*
    @brief ステートプール用マップからステートクラスを削除する関数
    @param	_stateTag 鍵となるタグ
    */
    void RemoveStatePoolMap(CameraState _stateTag);

    /*
    @brief ステートプール用マップをクリアする
    */
    void ClearStatePoolMap();

protected:

    // 移動先position
    Vector3 tmpMovePos;
    Vector3 tmpPosition;
    // 追従先のオブジェクト座標
    Vector3 lerpObjectPos;
    // view行列
    Matrix4 view;
    // プレイヤーのポインタを保持するための変数
    PlayerObject* playerObject;
    // 線形保管時にデルタタイムをかけるとき用の補正定数
    const float DeltaCorrection;
    // カメラ回転計算用のヨーとピッチ
    float yaw;
    float pitch;

    // 画角を変更するかどうか
    bool isChangeMode;

    // 間隔
    Vector3 offSetPosition;

    // 今のcameraのstate状態を保存するための変数
    CameraState nowState;
    // 変更された次のcameraのstate状態を保存するための変数
    CameraState nextState;

    // 全stateが格納されるマップ
    std::unordered_map<CameraState, CameraObjectStateBase*> statePoolMap;

public: // ゲッターセッター
    
    /*
    @brief カメラの前方ベクトルを得るためのgetter
    @return カメラの前方ベクトル
    */
    Vector3 GetCameraVec() const { return forwardVec; }

    /*
    @brief 追従するオブジェクトのポインタを得るためのgetter
    @return 追従するオブジェクトのポインタ
    */
    PlayerObject* GetLerpObject() const { return playerObject; }

    /*
    @brief 注視するオブジェクトのポジションのgetter
    @return 注視点
    */
    Vector3 GetLerpObjectPos() const { return lerpObjectPos; }

    /*
    @brief 追従するオブジェクトのとの間隔を取得
    @return 間隔
    */
    Vector3 GetOffsetPosition() const { return offSetPosition; }

    /*
    @brief 追従するオブジェクトのとの間隔を取得
    @return 間隔
    */
    bool GetIsChangeMode() const { return isChangeMode; }

    /*
    @brief	注視するオブジェクトのポジションをセット
    @param 見る対象物のポジション
    */
    void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }

    /*
    @brief	注視するオブジェクトのポジションをセット
    @param 見る対象物のポジション
    */
    void SetOffsetPosition(Vector3 _offset) { offSetPosition = _offset; }

    /*
    @brief	次のステータスをセット
    @param _nextState 次のステータス
    */
    void SetIsChangeMode(bool _isChangeMode) { isChangeMode = _isChangeMode; }

    /*
    @brief	前方ベクトルをセット
    @param _nextForward 次の前方ベクトル
    */
    void SetCameraVec(Vector3 _nextForward) { forwardVec = _nextForward; }
};