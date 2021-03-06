#pragma once
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
    ~TitleCameraObject();

    /*
    @brief	更新処理
    @param	deltaTime固定
    */
    void UpdateGameObject(float _deltaTime = 1.0f);
    void GameObjectInput(const InputState& _keyState);

private:

    Vector3 target;
    Matrix4 view;

};

