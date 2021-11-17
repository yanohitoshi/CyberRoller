#pragma once
#include "GameObject.h"

// クラスの前方宣言
class SkyBoxObject;

class StageSelectSceneUI :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    StageSelectSceneUI();

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

private:

    // スカイボックスクラスのポインタ
    SkyBoxObject* skyBox;
};

