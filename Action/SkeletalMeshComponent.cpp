//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"
#include "GameObject.h"

/*
@fn コンストラクタ
@param _owner 親となるGameObjectのポインタ
*/
SkeletalMeshComponent::SkeletalMeshComponent(GameObject* owner)
	:MeshComponent(owner, true,false)
	, skeleton(nullptr)
	, color(Vector3(0,0,0))
{
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void SkeletalMeshComponent::Draw(Shader* shader)                 
{
	//親オブジェクトが未更新状態でないか
	if (owner->GetState() != State::Dead)
	{
		if (mesh)
		{
			//ワールド変換をセット
			shader->SetMatrixUniform("uWorldTransform",
				owner->GetWorldTransform());
			// 行列パレットをセット    
			shader->SetMatrixUniforms("uMatrixPalette", &palette.mEntry[0],
				MaxSkeletonBones);
			//スペキュラー強度をセット
			shader->SetFloatUniform("uSpecPower", 25);

			shader->SetVectorUniform("uColor", color);

			luminance = owner->GetLuminance();
			shader->SetFloatUniform("uLuminance", luminance);

			SetTextureToShader(shader);

			//メッシュの頂点配列をアクティブに
			VertexArray* va = mesh->GetVertexArray();
			va->SetActive();
			//描画
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@brief　更新処理
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void SkeletalMeshComponent::Update(float _deltaTime)
{
		if (animation && skeleton)
		{
			animTime += _deltaTime * animPlayRate;
			if (animation->IsLoopAnimation())
			{
				//  アニメを巻き戻して再生
				while (animTime > animation->GetDuration())
				{
					animTime -= animation->GetDuration();
				}
			}
			// ループしないアニメで再生時間超えたら最終時間までとする
			else if (animTime > animation->GetDuration())
			{
				animTime = animation->GetDuration();
			}

			// 行列パレットの再計算
			ComputeMatrixPalette();
		}
	
}

/*
@fn アニメーションの再生
@param _anim アニメーションデータクラス
@param _playRate アニメーションの再生速度
@return アニメーションの残り時間
*/
float SkeletalMeshComponent::PlayAnimation(const Animation* _anim, float _playRate) 
{
	animation = _anim;
	animTime = 0.0f;
	animPlayRate = _playRate;

	if (!animation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return animation->GetDuration();
}

/*
@fn 行列パレットの計算
*/
void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// グローバル逆バインド行列配列の取得
	const std::vector<Matrix4>& globalInvBindPoses = skeleton->GetGlobalInvBindPoses();   
	// 現在のポーズ行列
	std::vector<Matrix4> currentPoses;                                        
	// アニメ時刻時点のグローバルポーズの取得
	animation->GetGlobalPoseAtTime(currentPoses, skeleton, animTime);      
	// それぞれのボーンの行列パレットのセット                                    
	for (size_t i = 0; i < skeleton->GetNumBones(); i++)
	{
		//行列パレット[i] = グローバル逆バインド行列[i]　×　現在のポーズ行列[i]  (iはボーンID)         
		palette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}

/*
@fn アニメーションが再生中か調べる関数
*/
bool SkeletalMeshComponent::IsPlaying()
{

	if (!animation->IsLoopAnimation())
	{
		if (animTime >= animation->GetDuration())
		{
			return false;
		}
	}

	return true;
}

/*
@fn textureセット用関数
@param _shader セットするシェーダーのポインタ
*/
void SkeletalMeshComponent::SetTextureToShader(Shader* _shader)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = mesh->GetTextureID(TextureStage::DIFFUSE_MAP); // ディフューズ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::NORMAL_MAP); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::SPECULAR_MAP); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::EMISSIVE_MAP); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}