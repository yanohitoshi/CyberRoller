//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyElectricShockEffect.h"

/*
@fn コンストラクタ
@param	親となるクラスのポインタ
@param	ポジション
*/
EnemyElectricShockEffect::EnemyElectricShockEffect(GameObject* _owner,const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 10, "Assets/Effect/Enemy/ElectricShock.png", false)
	, AddScale(12.0f)
	, SubAlpha(0.1f)
	, RandValue(361)
	, EffectColor(Vector3(0.65f, 0.65f, 1.0f))
{
	// メンバー変数の初期化
	scale = 64;
	alpha = 1.0f;
	speed = 1.5f;
	position = _pos;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(EffectColor);
	owner = _owner;
	particleComponent->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ADD);
	RotateEffect();
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
EnemyElectricShockEffect::~EnemyElectricShockEffect()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void EnemyElectricShockEffect::UpdateGameObject(float _deltaTime)
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

/*
@fn 回転処理関数
@brief	エフェクトの回転を行う
*/
void EnemyElectricShockEffect::RotateEffect()
{
	// X軸を回転
	Rotation(Vector3::UnitX);
	// Y軸を回転
	Rotation(Vector3::UnitY);
	// Z軸を回転
	Rotation(Vector3::UnitZ);

	// 回転値を用いて移動方向を計算
	Matrix4 mat = Matrix4::CreateFromQuaternion(this->GetRotation());
	velocity.x += mat.GetXAxis().x;
	velocity.y += mat.GetYAxis().y;
	velocity.z += mat.GetZAxis().z;
	velocity.Normalize();

}

/*
@fn 回転計算処理
@param _axis 回転軸
*/
void EnemyElectricShockEffect::Rotation(const Vector3 _axis)
{
	//ランダムな値回転させる
	float radian = Math::ToRadians((float)(rand() % RandValue));
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}