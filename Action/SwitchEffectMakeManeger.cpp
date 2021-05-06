#include "SwitchEffectMakeManeger.h"
#include "SwitchParticleEffect.h"

SwitchEffectMakeManeger::SwitchEffectMakeManeger(GameObject* _owner)
	: GameObject(false,Tag::PARTICLE)
	, SecondCorrectionValue(2.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, MaxEffects(15)
	, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = owner->GetPosition();
	ChackOnFlag = false;
	tmpChackOnFlag = false;
	generateFlag = false;

}

SwitchEffectMakeManeger::~SwitchEffectMakeManeger()
{
}

void SwitchEffectMakeManeger::UpdateGameObject(float _deltaTime)
{
	// ownerのフラグを保存
	ChackOnFlag = owner->GetSwitchFlag();

	// 前フレームのフラグと今のフラグが違っていたら
	if (ChackOnFlag != tmpChackOnFlag)
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
		// 生成フラグをtrueに
		generateFlag = true;
	}
	
	// パーティクルの状態を見て
	switch (particleState)
	{
		// 無効状態だったらbreak
	case (PARTICLE_DISABLE):
		break;
		// 有効状態だったら
	case PARTICLE_ACTIVE:


		//particleが発生するフレームの条件式を書く
		if (generateFlag == true)
		{
			for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
			{
				// ランダムな値を生成
				Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue)/ CorrectionRandValue + SecondCorrectionValue);
				
				// 値が大きすぎるので最後の補正をかけて速度に代入
				velocity = randV * LastCorrection;

				// 速度を一時保存
				Vector3 vel = velocity;

				//ランダムな値を渡す
				vel = vel + randV;

				// 2・3の倍数の際速度ベクトルをそれぞれｘもしくはyを逆方向に変換
				// 2の倍数の時はｘ、3の倍数の時はｙ
				if (efectCount % 2 == 0)
				{
					vel.x *= -1.0f;
				}
				else if (efectCount % 3 == 0)
				{
					vel.y *= -1.0f;
				}
				
				// いろいろな方向に飛ばしたいため
				// 4・6の倍数の際速度ベクトルをそれぞれｘもしくはyを逆方向に変換
				// 6の倍数の時はｘ、4の倍数の時はｙ
				if (efectCount % 4 == 0)
				{
					vel.y *= -1.0f;
				}
				else if (efectCount % 6 == 0)
				{
					vel.x *= -1.0f;
				}

				// ownerのポジションを代入
				position = owner->GetPosition();
				//particleを生成
				new SwitchParticleEffect(position, vel);
			}

			// 生成フラグをfalseに
			generateFlag = false;
		}

		// particleStateを無効化してbreak
		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}
	
	// フラグを保存
	tmpChackOnFlag = ChackOnFlag;

}

