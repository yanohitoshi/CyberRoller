#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectBase.h"

/*
@file TitleCamre.h
@brief タイトル画面を映すカメラの生成と更新処理
       CameraObjectBaseを継承
*/
class TitleCameraObject :
    public CameraObjectBase
{
public:

    /*
    @brief	コンストラクタ
    @param	ポジション
    */
    TitleCameraObject(const Vector3 _pos);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TitleCameraObject();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	deltaTime固定
    */
    void UpdateGameObject(float _deltaTime = 1.0f);
    
    /*
    @fn 入力を引数で受け取る更新関数
    @brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
    */
    void GameObjectInput(const InputState& _keyState);

private:

    // タイトル用プレイヤーのポジションを利用して生成するので位置をずらすための定数
    const float ShiftPosition;

    // 少し先を注視するようにしたいのでZ軸をずらす定数
    const float ShiftGazePoint;

    // 見る場所のターゲットVector3
    Vector3 target;

    // view行列
    Matrix4 view;

};

