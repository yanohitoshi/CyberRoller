#pragma once
#include "ParticleEffectBase.h"

class EnemyObjectBase;

class EnemyDeadEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    EnemyDeadEffect(GameObject* _owner,const Vector3& _pos);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~EnemyDeadEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 毎フレーム足すscale値 
    const float AddScale;
    // 毎フレーム引くalpha値
    const float SubAlpha;

};

