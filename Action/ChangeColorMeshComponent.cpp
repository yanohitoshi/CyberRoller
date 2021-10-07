//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ChangeColorMeshComponent.h"
#include "MeshComponent.h"
#include "GameObject.h"
#include "Shader.h"
#include "Renderer.h"

/*
@fn コンストラクタ
@param _owner 親となるGameObjectのポインタ
@param _skelton スケルトンデータを用いるか
@param _color 途中で色の変更を用いるか
*/
ChangeColorMeshComponent::ChangeColorMeshComponent(GameObject* _owner, bool _skelton,bool _color)
	:MeshComponent(_owner, _skelton,_color)
{
}

/*
@fn デストラクタ
@brief  componentの削除を行う
*/
ChangeColorMeshComponent::~ChangeColorMeshComponent()
{
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void ChangeColorMeshComponent::Draw(Shader* _shader)
{
	// 色情報を送る
	_shader->SetVectorUniform("uColor", color);
	//通常のメッシュコンポーネントの描画
	MeshComponent::Draw(_shader);
}