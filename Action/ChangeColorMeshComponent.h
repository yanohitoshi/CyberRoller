#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MeshComponent.h"
#include "Math.h"

/*
 @file ChangeColorMeshComponent.h
 @brief MeshComponentを継承したゲーム中にshaderを使用して色を変更することができるComponentクラス
*/
class ChangeColorMeshComponent :
    public MeshComponent
{
public:

    /*
    @fn コンストラクタ
    @param _owner 親となるGameObjectのポインタ
    @param _skelton スケルトンデータを用いるか
    @param _color 途中で色の変更を用いるか
    */
    ChangeColorMeshComponent(GameObject* _owner, bool _skelton, bool _color);
    
    /*
    @fn デストラクタ
    @brief  componentの削除を行う
    */
    ~ChangeColorMeshComponent();

    /*
    @brief　描画処理
    @param	_shader 使用するシェーダークラスのポインタ
    */
    void Draw(Shader* _shader)override;

private:

    // 色情報を持つVector3変数
    Vector3 color;

public:// ゲッターセッター

    /*
    @brief  color変数のsetter
    @param  _color 変更したい色のRGB(Vector3)
    */
    void SetColor(const Vector3& _color) { color = _color; }
};

