#pragma once
#include "ParticleEffectBase.h"

/*
@file MoveTutorialParticl.h
@brief 移動用チュートリアルのParticlEffectの表示を行う
*/
class MoveTutorialParticl :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	コンストラクタ
    @param	ポジション
    */
    MoveTutorialParticl(const Vector3& _pos);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~MoveTutorialParticl()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
};

