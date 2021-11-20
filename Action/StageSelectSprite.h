#pragma once
#include "GameObject.h"

class SpriteComponent;
class StageSelectSceneUI;

class StageSelectSprite :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    */
    StageSelectSprite(StageSelectSceneUI* _owner,SceneState _state,const std::string& _spriteFileName);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~StageSelectSprite();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 背景用スプライトComponent
    SpriteComponent* sprite;
    SceneState myState;

    void MoveLeft();
    void MoveRight();
    bool isVisible;

public:

    void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }
};

