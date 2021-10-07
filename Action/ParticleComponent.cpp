//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleComponent.h"
#include "Shader.h"
#include "Renderer.h"
#include "GameObject.h"

// �r���{�[�h�s��
Matrix4 ParticleComponent::staticBillboardMat;
// �J�����̃��[���h���W
Vector3 ParticleComponent::staticCameraWorldPos;

/*
@fn �R���X�g���N�^
@param _offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
@param _scale �摜�̕`��T�C�Y
*/
ParticleComponent::ParticleComponent(GameObject* _owner, bool _useStaticBillboardMat,const Vector3& _offset, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, offset(_offset)
	, scale(_scale)
	, alpha(1.0f)
	, blendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, visible(true)
	, drawOrder(_updateOrder)
	, color(Vector3(1, 1, 1))
	, reverce(false)
	, textureID(0)
	, useStaticBillboardMat(_useStaticBillboardMat)
	, owner(_owner)
{
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveParticle(this);
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void ParticleComponent::Draw(Shader* _shader)
{
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (owner->GetState() == State::Dead)
	{
		return;
	}
	Matrix4 mat, matScale;
	
	matScale = Matrix4::CreateScale(scale);
	mat = Matrix4::CreateTranslation(owner->GetPosition());

	// �J�����̕����Ɍ������邩�ǂ����̔�r������ĕ��򂳂���
	// �������Ȃ��ꍇ�̓I�u�W�F�N�g�̉�]�l���Q�Ƃ���
	if (useStaticBillboardMat)
	{
		_shader->SetMatrixUniform("uWorldTransform", matScale * staticBillboardMat * mat);
	}
	else
	{
		// texture�̌�����90�x��]������
		Matrix4 offset = Matrix4::CreateRotationZ(Math::ToRadians(90.0f));
		// object��Rotation���Q�Ƃ�particle�̌��������肷��
		Matrix4 objectMatrix = Matrix4::CreateFromQuaternion(owner->GetRotation());
		_shader->SetMatrixUniform("uWorldTransform", matScale * objectMatrix * offset * mat);
		}
	_shader->SetFloatUniform("uAlpha", alpha);
	_shader->SetVectorUniform("uColor", color);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// �J���������ł̃\�[�g�p
bool ParticleComponent::operator<(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - offset).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.offset).LengthSq();
	return lenThis < lenRhs;
}

// �J���������ł̃\�[�g�p
bool ParticleComponent::operator>(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - offset).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.offset).LengthSq();
	return lenThis > lenRhs;
}

/*
@return �r���{�[�h�s��(Matrix4)
*/
Matrix4 GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[2][2] *= -1;

	Matrix4 rot;
	rot = Matrix4::CreateRotationX(-0.5f * 3.14159f);
	ret =  rot * ret;

	return Matrix4(ret);
}