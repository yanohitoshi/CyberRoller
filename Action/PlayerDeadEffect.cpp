#include "PlayerDeadEffect.h"

PlayerDeadEffect::PlayerDeadEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _distance)
	: ParticleEffectBase(_pos, Vector3::Zero, 15, "Assets/Effect/Thunder_Thin.png", false)
	, AddScale(4.0f)
	, SubAlpha(0.1f)
	, RandValue(361)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
{
	// メンバー変数の初期化
	scale = 32;
	alpha = 1.0f;
	speed = 1.0f;
	position = _pos + _distance;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
	RotateEffect();
}

PlayerDeadEffect::~PlayerDeadEffect()
{
}

void PlayerDeadEffect::UpdateGameObject(float _deltaTime)
{
	// 生存時間のカウントダウン
	ParticleEffectBase::LifeCountDown();

	// ライフカウントが0以上になったら
	if (lifeCount >= 0)
	{
		// 定数を足して拡大
		scale += AddScale;
		// 定数を引いて透過
		alpha -= SubAlpha;

		// scale値をセット
		particleComponent->SetScale(scale);
		// alpha値をセット
		particleComponent->SetAlpha(alpha);

		// ポジションに速度を追加
		position += velocity * speed;
		// ポジションを更新
		SetPosition(position);
	}

	// ライフカウントが0以下になったら
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
	}
}

// @fix
void PlayerDeadEffect::RotateEffect()
{
	float radian;
	Quaternion rot;
	Quaternion target;

	//X軸をランダムな値回転させる
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radian);
	target = Quaternion::Concatenate(rot, incX);
	SetRotation(target);

	//Y軸をランダムな値回転させる
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radian);
	target = Quaternion::Concatenate(rot, incY);
	SetRotation(target);

	//Z軸をランダムな値回転させる
	radian = Math::ToRadians((float)(rand() % RandValue));
	rot = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radian);
	target = Quaternion::Concatenate(rot, incZ);
	SetRotation(target);

	// 回転値から移動方向を計算
	Matrix4 mat = Matrix4::CreateFromQuaternion(this->GetRotation());
	velocity.x += mat.GetXAxis().x;
	velocity.y += mat.GetYAxis().y;
	velocity.z += mat.GetZAxis().z;
	velocity.Normalize();

}
