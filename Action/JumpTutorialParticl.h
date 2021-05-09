#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file JumpTutorialParticl.h
@brief ジャンプ用チュートリアルのParticlEffect表示を行う
*/
class JumpTutorialParticl :
    public ParticleEffectBase
{
public:

    /*
    @brief	コンストラクタ
    @param	ポジション
    */
    JumpTutorialParticl(const Vector3& _pos);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~JumpTutorialParticl()override;

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

