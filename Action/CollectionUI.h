#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class CollectionObject;
class CollectedSprite;
class UnCollectedSprite;
class CollectedEffectSprite;

/*
@file CollectionUI.h
@brief 収集物用UIを管理するクラス
*/
class CollectionUI :
    public GameObject
{
public:
    
    /*
    @brief	コンストラクタ
    */
    CollectionUI(CollectionObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CollectionUI()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @fn 通常時の描画
    */
    void DrawInGame();

    /*
    @fn 描画をリセットする
    */
    void ResetDraw();

    /*
    @fn 描画するポジションを変更する
    @param _position セットする位置
    */
    void SetDrawPosition(Vector3 _position);

private:

    // オーナーとなる収集物のポインタ変数
    CollectionObject* owner;

    // それぞれのspriteのポインタ変数
    CollectedSprite* collectedSprite;
    UnCollectedSprite* unCollectedSprite;
    CollectedEffectSprite* collectedEffectSprite;

    // ゲーム中かどうか
    bool isInGame;
};

