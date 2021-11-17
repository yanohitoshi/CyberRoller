#pragma once
#include "GameObject.h"

class SpriteComponent;

class StageUnSelectIcon :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    */
    StageUnSelectIcon(Vector3& _pos, const std::string& _spriteFileName);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~StageUnSelectIcon();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 背景用スプライトComponent
    SpriteComponent* sprite;
};

