//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CubeMapComponent.h"
#include "Texture.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"

/*
@fn コンストラクタ
@param _owner 親クラスのポインタ
*/
CubeMapComponent::CubeMapComponent(GameObject* _owner)
	: Component(_owner)
	, texture(nullptr)
	, luminance(1.0f)
	, isVisible(true)
{
}

/*
@fn デストラクタ
@brief  Componentの削除を行う
*/
CubeMapComponent::~CubeMapComponent()
{
	delete texture;
}

/*
@brief　texture生成処理
@param	in_filePath 使用するtextureのファイルパス
*/
void CubeMapComponent::CreateTexture(const std::string& in_filePath)
{
	texture = new Texture();
	texture->LoadCubeMap(in_filePath);
}

/*
@brief　描画処理
@param	in_shader 使用するシェーダークラスのポインタ
*/
void CubeMapComponent::Draw(Shader* in_shader)
{
	// 透明にしていなければ
	if (isVisible)
	{
		// 深度設定
		glDepthFunc(GL_LEQUAL);
		// 輝度情報をシェーダに渡す
		in_shader->SetFloatUniform("u_skyLuminance", luminance);
		// テクスチャバインド
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetTextureID());
		// キューブマップ用頂点配列のアクティブ化
		RENDERER->GetCubeMapVerts()->SetActive();
		// 描画
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 念のためバインド解除
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);
	}
}