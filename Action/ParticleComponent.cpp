//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleComponent.h"
#include "Shader.h"
#include "Renderer.h"
#include "GameObject.h"

// ビルボード行列
Matrix4 ParticleComponent::staticBillboardMat;
// カメラのワールド座標
Vector3 ParticleComponent::staticCameraWorldPos;

/*
@fn コンストラクタ
@param _offset 親オブジェクトクラスと画像を描画する位置の差
@param _scale 画像の描画サイズ
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
	//レンダラーにポインターを送る
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveParticle(this);
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void ParticleComponent::Draw(Shader* _shader)
{
	//親オブジェクトが未更新状態でないか
	if (owner->GetState() == State::Dead)
	{
		return;
	}
	Matrix4 mat, matScale;
	
	matScale = Matrix4::CreateScale(scale);
	mat = Matrix4::CreateTranslation(owner->GetPosition());

	// カメラの方向に向かせるかどうかの比較を取って分岐させる
	// 向かせない場合はオブジェクトの回転値を参照する
	if (useStaticBillboardMat)
	{
		_shader->SetMatrixUniform("uWorldTransform", matScale * staticBillboardMat * mat);
	}
	else
	{
		// textureの向きを90度回転させる
		Matrix4 offset = Matrix4::CreateRotationZ(Math::ToRadians(90.0f));
		// objectのRotationを参照しparticleの向きを決定する
		Matrix4 objectMatrix = Matrix4::CreateFromQuaternion(owner->GetRotation());
		_shader->SetMatrixUniform("uWorldTransform", matScale * objectMatrix * offset * mat);
		}
	_shader->SetFloatUniform("uAlpha", alpha);
	_shader->SetVectorUniform("uColor", color);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// カメラ距離でのソート用
bool ParticleComponent::operator<(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - offset).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.offset).LengthSq();
	return lenThis < lenRhs;
}

// カメラ距離でのソート用
bool ParticleComponent::operator>(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - offset).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.offset).LengthSq();
	return lenThis > lenRhs;
}

/*
@return ビルボード行列(Matrix4)
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