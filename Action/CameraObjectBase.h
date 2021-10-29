#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

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

    //移動先position
    Vector3 tmpMovePos;
    Vector3 tmpPosition;
    //追従先のオブジェクト座標
    Vector3 lerpObjectPos;
    // view行列
    Matrix4 view;
    // プレイヤーのポインタを保持するための変数
    PlayerObject* playerObject;
    // 線形保管時にデルタタイムをかけるとき用の補正定数
    const float DeltaCorrection;
    //カメラ回転計算用のヨーとピッチ
    float yaw;
    float pitch;

    Vector3 offSetPosition;

    // 今のenemyのstate状態を保存するための変数
    CameraState nowState;
    // 変更された次のenemyのstate状態を保存するための変数
    CameraState nextState;
    // 全stateが格納されるマップ
    std::unordered_map<CameraState, CameraObjectStateBase*> statePoolMap;

private:


public:
    
    /*
    @brief カメラの前方ベクトルを得るためのgetter
    @return カメラの前方ベクトル
    */
    Vector3 GetCameraVec() { return forwardVec; }

    /*
    @brief 追従するオブジェクトのポインタを得るためのgetter
    @return 追従するオブジェクトのポインタ
    */
    PlayerObject* GetLerpObject() { return playerObject; }

    /*
    @brief player以外のものを注視する場合のポジション得るためのgetter
    @return 注視点
    */
    Vector3 GetLerpObjectPos() { return lerpObjectPos; }

    /*
    @brief	player以外のものを注視する際に使うsetter
    @param 見る対象物のポジション
    */
    void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }

    Vector3 GetOffsetPosition() { return offSetPosition; }

    void SetOffsetPosition(Vector3 _offset) { offSetPosition = _offset; }

    void SetNextState(CameraState _nextState) { nextState = _nextState; }
    void SetCameraVec(Vector3 _nextForward) { forwardVec = _nextForward; }
};

