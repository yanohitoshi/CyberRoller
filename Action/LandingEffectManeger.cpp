#include "LandingEffectManeger.h"
#include "LandingEffect.h"
#include "PlayerObject.h"

LandingEffectManeger::LandingEffectManeger(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(8)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
	tmpVelZ = 0.0f;
}

LandingEffectManeger::~LandingEffectManeger()
{
}

void LandingEffectManeger::UpdateGameObject(float _deltaTime)
{
	// 前のフレームでZ軸の速度が0.0fでなくこのフレームでのZ軸の速度0.0fでかつジャンプフラグがfalseだったら
	if (owner->GetVelocity().z == 0.0f && tmpVelZ != 0.0f && PlayerObject::GetChackJumpFlag() == false)
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// パーティクルを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// パーティクルの状態を見て
	switch (particleState)
	{
		// 無効状態だったらbreak
	case (PARTICLE_DISABLE):
		break;
		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// ownerのポジションを得る
		position = owner->GetPosition();

		// 8個生成
		for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
		{
			// 八方向に動かすのでそれぞれに方向ベクトルを渡す
			if (efectCount == 0)
			{
				velocity = Vector3::UnitX;

			}
			if (efectCount == 1)
			{
				velocity = Vector3::UnitY;
			}
			if (efectCount == 2)
			{
				velocity = Vector3::NegUnitX;
			}
			if (efectCount == 3)
			{
				velocity = Vector3::NegUnitY;
			}
			if (efectCount == 4)
			{
				velocity = Vector3::UnitX + Vector3::UnitY;
			}
			if (efectCount == 5)
			{
				velocity = Vector3::UnitX + Vector3::NegUnitY;
			}
			if (efectCount == 6)
			{
				velocity = Vector3::NegUnitX + Vector3::UnitY;
			}
			if (efectCount == 7)
			{
				velocity = Vector3::NegUnitX + Vector3::NegUnitY;
			}

			//particleを生成
			new LandingEffect(position, velocity);
		}

		// particleState無効に
		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}

	// ownerのZ軸速度を保存
	tmpVelZ = owner->GetVelocity().z;

}
