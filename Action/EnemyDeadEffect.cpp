#include "EnemyDeadEffect.h"

EnemyDeadEffect::EnemyDeadEffect(GameObject* _owner,const Vector3& _pos)
	: ParticleEffectBase(_pos, Vector3::Zero, 30, "Assets/Effect/Thunder_Thin.png", false)
	, AddScale(4.0f)
	, SubAlpha(0.01f)
{
	// メンバー変数の初期化
	scale = 64.0f;
	alpha = 1.0f;
	position = _pos;
	position.z += 20.0f;
	particleComponent->SetScale(scale);
	particleComponent->SetAlpha(alpha);
	particleComponent->SetColor(Vector3(0.65f, 0.65f, 1.0f));
	owner = _owner;

	Vector3 forward = owner->GetForwardVec();
	if (forward.x > 0.0f)
	{
		position.x += 50.0f;
	}
	else if (forward.x < 0.0f)
	{
		position.x -= 50.0f;
	}
	else if (forward.y > 0.0f)
	{
		position.y += 50.0f;
	}
	else if (forward.y < 0.0f)
	{
		position.y -= 50.0f;
	}
	//Z軸を10度回転させる
	float radianX = Math::ToRadians((float)(rand() % 361));
	Quaternion rotX = this->GetRotation();
	Quaternion incX(Vector3::UnitX, radianX);
	Quaternion targetX = Quaternion::Concatenate(rotX, incX);
	SetRotation(targetX);

	//Z軸を10度回転させる
	float radianY = Math::ToRadians((float)(rand() % 361));
	Quaternion rotY = this->GetRotation();
	Quaternion incY(Vector3::UnitY, radianY);
	Quaternion targetY = Quaternion::Concatenate(rotY, incY);
	SetRotation(targetY);

	//Z軸を10度回転させる
	float radianZ = Math::ToRadians((float)(rand() % 361));
	Quaternion rotZ = this->GetRotation();
	Quaternion incZ(Vector3::UnitZ, radianZ);
	Quaternion targetZ = Quaternion::Concatenate(rotZ, incZ);
	SetRotation(targetZ);
}

EnemyDeadEffect::~EnemyDeadEffect()
{
}

void EnemyDeadEffect::UpdateGameObject(float _deltaTime)
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