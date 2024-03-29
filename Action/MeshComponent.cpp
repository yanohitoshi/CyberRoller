//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "RenderingObjectManager.h"
#include "VertexArray.h"
#include "Texture.h"

/*
@param _skelton スケルトンデータを用いるか。
@sa SkeletalMeshComponent.h
*/
MeshComponent::MeshComponent(GameObject* _owner, bool _skelton,bool _color)
	:Component(_owner)
	, mesh(nullptr)
	, textureIndex(0)
	, visible(true)
	, isSkelton(_skelton)
	, isColorChange(_color)
	, emissiveColor(Vector3(1.0f, 1.0f, 1.0f))
{
	//レンダラーにポインターを送る
	RENDERING_OBJECT_MANAGER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	//レンダラーからポインタを削除する
	RENDERING_OBJECT_MANAGER->RemoveMeshComponent(this);
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void MeshComponent::Draw(Shader* _shader)
{
	// オーナーのstateがDeadじゃなければ
	if (owner->GetState() != State::Dead)
	{
		if (mesh)
		{

			_shader->SetMatrixUniform("uWorldTransform",owner->GetWorldTransform());

			_shader->SetFloatUniform("uSpecPower", mesh->GetSpecPower());

			luminance = owner->GetLuminance();

			_shader->SetFloatUniform("uLuminance", luminance);

			if (!isColorChange)
			{
				_shader->SetVectorUniform("uColor", emissiveColor);
			}

			SetTextureToShader(_shader);

			VertexArray* va = mesh->GetVertexArray();
			va->SetActive();

			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@brief　使用するtextureをセットする
@param	_shader 使用するシェーダークラスのポインタ
*/
void MeshComponent::SetTextureToShader(Shader* shader)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = mesh->GetTextureID(TextureStage::DIFFUSE_MAP); // ディフューズ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::NORMAL_MAP); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::SPECULAR_MAP); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::EMISSIVE_MAP); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}