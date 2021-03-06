#pragma once
#include "GameObject.h"

//GameObjectを継承したカメラの基底クラス
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @brief	コンストラクタ
    @param	再利用するかフラグ
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);
    ~CameraObjectBase();

    /*
    @brief	更新処理
    @param	最後のフレームを完了するのに要した時間
    */
    virtual void UpdateGameObject(float _deltaTime = 1.0f);
    virtual void GameObjectInput(const InputState& _keyState);

private:

};

