#pragma once
#include "GameObject.h"

class SpriteComponent;
class StageSelectSceneUI;

class StageSelectIconSprite :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    */
    StageSelectIconSprite(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~StageSelectIconSprite();

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

    bool isVisible;

public:
    
    void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }

};

