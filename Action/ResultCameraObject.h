#pragma once
#include "CameraObjectBase.h"

/*
@file ResultCameraObject.h
@brief リザルトシーンでのカメラclass
*/
class ResultCameraObject :
    public CameraObjectBase
{
public:

    /*
    @brief	コンストラクタ
    @param	カメラの注視点
    */
    ResultCameraObject(const Vector3 _pos);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ResultCameraObject();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	deltaTime固定
    */
    void UpdateGameObject(float _deltaTime = 1.0f);

private:

    // カメラの注視点を利用して生成するので位置をずらすための定数
    const float ShiftPosition;

    // 見る場所のターゲットVector3
    Vector3 target;

    // view行列
    Matrix4 view;
};

