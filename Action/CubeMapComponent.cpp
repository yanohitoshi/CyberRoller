#include "CubeMapComponent.h"
#include "Texture.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"


CubeMapComponent::CubeMapComponent(GameObject* _owner)
	: Component(_owner)
	, texture(nullptr)
	, luminance(1.0f)
	, isVisible(true)
{
}

CubeMapComponent::~CubeMapComponent()
{
	delete texture;
}

void CubeMapComponent::CreateTexture(const std::string& in_filePath)
{
	texture = new Texture();
	texture->LoadCubeMap(in_filePath);
}

void CubeMapComponent::Draw(Shader* in_shader)
{
	// �����ɂ��Ă��Ȃ����
	if (isVisible)
	{
		// �[�x�ݒ�
		glDepthFunc(GL_LEQUAL);
		// �P�x�����V�F�[�_�ɓn��
		in_shader->SetFloatUniform("u_skyLuminance", luminance);
		// �e�N�X�`���o�C���h
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetTextureID());
		// �L���[�u�}�b�v�p���_�z��̃A�N�e�B�u��
		RENDERER->GetCubeMapVerts()->SetActive();
		// �`��
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// �O�̂��߃o�C���h����
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);

	}
}
