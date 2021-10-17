#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

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
    @brief	player以外のものを注視する際に使うsetter
    @param 見る対象物のポジション
    */
    void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }

    /*
    @brief リスポーンしたときにカメラの位置を初期状態にセットする関数
    */
    void ResetCamera() { yaw = Math::ToRadians(180); pitch = Math::ToRadians(30); }

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
    //カメラ回転計算用のヨーとピッチ
    float yaw;
    float pitch;
private:

public:
    
    /*
    @brief カメラの前方ベクトルを得るためのgetter
    @param カメラの前方ベクトル
    */
    Vector3 GetCameraVec() { return forwardVec; }

};

