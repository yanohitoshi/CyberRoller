//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
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
@fn �R���X�g���N�^
@param _owner �e�ƂȂ�GameObject�̃|�C���^
*/
SkeletalMeshComponent::SkeletalMeshComponent(GameObject* owner)
	:MeshComponent(owner, true,false)
	, skeleton(nullptr)
	, color(Vector3(0,0,0))
{
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SkeletalMeshComponent::Draw(Shader* shader)                 
{
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (owner->GetState() != State::Dead)
	{
		if (mesh)
		{
			//���[���h�ϊ����Z�b�g
			shader->SetMatrixUniform("uWorldTransform",
				owner->GetWorldTransform());
			// �s��p���b�g���Z�b�g    
			shader->SetMatrixUniforms("uMatrixPalette", &palette.mEntry[0],
				MaxSkeletonBones);
			//�X�y�L�����[���x���Z�b�g
			shader->SetFloatUniform("uSpecPower", 25);

			shader->SetVectorUniform("uColor", color);

			luminance = owner->GetLuminance();
			shader->SetFloatUniform("uLuminance", luminance);

			SetTextureToShader(shader);

			//���b�V���̒��_�z����A�N�e�B�u��
			VertexArray* va = mesh->GetVertexArray();
			va->SetActive();
			//�`��
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@brief�@�X�V����
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void SkeletalMeshComponent::Update(float _deltaTime)
{
		if (animation && skeleton)
		{
			animTime += _deltaTime * animPlayRate;
			if (animation->IsLoopAnimation())
			{
				//  �A�j���������߂��čĐ�
				while (animTime > animation->GetDuration())
				{
					animTime -= animation->GetDuration();
				}
			}
			// ���[�v���Ȃ��A�j���ōĐ����Ԓ�������ŏI���Ԃ܂łƂ���
			else if (animTime > animation->GetDuration())
			{
				animTime = animation->GetDuration();
			}

			// �s��p���b�g�̍Čv�Z
			ComputeMatrixPalette();
		}
	
}

/*
@fn �A�j���[�V�����̍Đ�
@param _anim �A�j���[�V�����f�[�^�N���X
@param _playRate �A�j���[�V�����̍Đ����x
@return �A�j���[�V�����̎c�莞��
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
@fn �s��p���b�g�̌v�Z
*/
void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// �O���[�o���t�o�C���h�s��z��̎擾
	const std::vector<Matrix4>& globalInvBindPoses = skeleton->GetGlobalInvBindPoses();   
	// ���݂̃|�[�Y�s��
	std::vector<Matrix4> currentPoses;                                        
	// �A�j���������_�̃O���[�o���|�[�Y�̎擾
	animation->GetGlobalPoseAtTime(currentPoses, skeleton, animTime);      
	// ���ꂼ��̃{�[���̍s��p���b�g�̃Z�b�g                                    
	for (size_t i = 0; i < skeleton->GetNumBones(); i++)
	{
		//�s��p���b�g[i] = �O���[�o���t�o�C���h�s��[i]�@�~�@���݂̃|�[�Y�s��[i]  (i�̓{�[��ID)         
		palette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}

/*
@fn �A�j���[�V�������Đ��������ׂ�֐�
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
@fn texture�Z�b�g�p�֐�
@param _shader �Z�b�g����V�F�[�_�[�̃|�C���^
*/
void SkeletalMeshComponent::SetTextureToShader(Shader* _shader)
{
	// ���b�V���e�N�X�`���Z�b�g
	int texID, stageCount = 0;
	texID = mesh->GetTextureID(TextureStage::DIFFUSE_MAP); // �f�B�t���[�Y
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::NORMAL_MAP); // �@���}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::SPECULAR_MAP); // �X�y�L�����[�}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}

	texID = mesh->GetTextureID(TextureStage::EMISSIVE_MAP); // ���ȕ��˃}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}