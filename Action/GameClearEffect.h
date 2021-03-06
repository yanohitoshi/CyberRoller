#pragma once

#include "ParticleEffectBase.h"

class GameClearEffect
	: public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    GameClearEffect(const Vector3& _pos, const Vector3& _velocity);
    ~GameClearEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;

};

