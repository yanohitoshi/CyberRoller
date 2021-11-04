#pragma once
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class Mesh;

class DebrisEffectObject :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	親となるクラスのポインタ
    @param	ポジション
    @param	移動速度
    */
    DebrisEffectObject(const Vector3& _pos, const Vector3& _direction);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~DebrisEffectObject()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    void LifeCountDown();

    // Meshを管理するクラス
    Mesh* mesh;
    // 3Dモデルの描画を行うクラス
    MeshComponent* meshComponent;

    Vector3 direction;
    int lifeCount;

    float moveSpeed;
    const float MovePower;

    //// 毎フレーム足すscale値 
    //const float AddScale;
    //// 毎フレーム引くalpha値
    //const float SubAlpha;
    //// エフェクトの色
    //const Vector3 EffectColor;
};

