#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include <unordered_map>

// クラスの前方宣言
class StageSelectScene;
class SkyBoxObject;
class StageSelectIconSprite;
class StageUnSelectIcon;
class StageSelectSprite;

/*
@file StageSelectSceneUI.h
@brief StageSelectSceneのUI表示を行う
*/
class StageSelectSceneUI :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    @param _owner 親クラスとなるsceneクラスのポインタ
    */
    StageSelectSceneUI(StageSelectScene* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~StageSelectSceneUI()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief 選択されている状態のアイコン用マップにスプライトクラスを追加する関数
    @param	_state 追加するスプライトクラスのポインタ
    @param	_stateTag 鍵となるタグ
    */
    void AddSelectIconSpriteMap(StageSelectIconSprite* _sprite, SceneState _stateTag);

    /*
    @brief 選択されている状態のアイコン用マップからスプライトクラスを削除する関数
    @param	_stateTag 鍵となるタグ
    */
    void RemoveSelectIconSpriteMap(SceneState _stateTag);

    /*
    @brief 選択されていない状態のアイコン用マップにスプライトクラスを追加する関数
    @param	_state 追加するスプライトクラスのポインタ
    @param	_stateTag 鍵となるタグ
    */
    void AddUnSelectIconSpriteMap(StageUnSelectIcon* _sprite, SceneState _stateTag);

    /*
    @brief 選択されていない状態のアイコン用マップからスプライトクラスを削除する関数
    @param	_stateTag 鍵となるタグ
    */
    void RemoveUnSelectIconSpriteMap(SceneState _stateTag);

    /*
    @brief stage選択画面のスプライトクラス用マップにスプライトクラスを追加する関数
    @param	_state 追加するスプライトクラスのポインタ
    @param	_stateTag 鍵となるタグ
    */
    void AddStageSelectSpriteMap(StageSelectSprite* _sprite, SceneState _stateTag);

    /*
    @brief 選択されていない状態のアイコン用マップからスプライトクラスを削除する関数
    @param	_stateTag 鍵となるタグ
    */
    void RemoveStageSelectSpriteMap(SceneState _stateTag);

private:

    // スカイボックスクラスのポインタ
    SkyBoxObject* skyBox;

    // オーナーのポインタ
    StageSelectScene* owner;

    /*
    @brief 全てのspriteマップをクリアする
    */
    void ClearAllSpriteMap();

    /*
    @brief 全てのspriteマップを生成する
    */
    void CreatStageSelectSprite();

    /*
    @brief 第1stageが選ばれている時の描画状態をセットする
    */
    void SetFirstStageSprite();     
   
    /*
    @brief 第2stageが選ばれている時の描画状態をセットする
    */
    void SetSecondStageSprite();
    
    /*
    @brief 第3stageが選ばれている時の描画状態をセットする
    */
    void SetThirdStageSprite();
    
    /*
    @brief 第4stageが選ばれている時の描画状態をセットする
    */
    void SetFourthStageSprite();
    
    /*
    @brief 第5stageが選ばれている時の描画状態をセットする
    */
    void SetFinalStageSprite();

    // StageSelectIconSpriteを格納するMap
    std::unordered_map<SceneState, StageSelectIconSprite*> selectIconSpriteMap;

    // StageUnSelectIconを格納するMap
    std::unordered_map<SceneState, StageUnSelectIcon*> unSelectIconMap;

    // StageSelectSpriteを格納するMap
    std::unordered_map<SceneState, StageSelectSprite*> selectSpriteMap;
};

