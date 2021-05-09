#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file TutorialSwitchOkEffect.h
@brief OK状態のスイッチのチュートリアル描画を行う
*/
class TutorialSwitchOkEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	コンストラクタ
    @param	ポジション
    @param	オーナーとなるGameObject型ポインタ
    */
    TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TutorialSwitchOkEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 拡大縮小値の初期化定数
    const float InitScale;

};

