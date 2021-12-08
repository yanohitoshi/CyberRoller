#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class StageSelectSceneUI;

/*
@file StageSelectSprite.h
@brief 選択されているstage画像を表示する
*/
class StageSelectSprite :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @parma 親クラスのポインタ
    @parma シーンのステータス
    @parma 描画する画像のファイルネーム
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
    // 自分のシーンステータス
    SceneState myState;

    // 描画を行うか否か
    bool isVisible;

public:

    /*
    @fn 描画を行うか否かをセットする
    @param _isVisible　描画するかどうか
    */
    void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }
};