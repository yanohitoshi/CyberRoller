#include "FireWorksEffectManeger.h"
#include "FierWorksEffect.h"
FireWorksEffectManeger::FireWorksEffectManeger(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, MaxEffects(24)
	, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	crystalColor = CrystalColor::WHITE;
}

FireWorksEffectManeger::~FireWorksEffectManeger()
{
}

void FireWorksEffectManeger::UpdateGameObject(float _deltaTime)
{
	// ownerのステータスがdeadになったら
	if (owner->GetState() == State::Dead)
	{
		// particleStateを有効化に
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleStateを無効化に
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

		// エフェクトの生成
		ActiveEffectProcess();

		break;

	}

}

void FireWorksEffectManeger::ActiveEffectProcess()
{
	// ownerのポジションを得る
	position = owner->GetPosition();

	// 生成フラグがtrueだったら
	if (generateFlag == true)
	{
		// エフェクト生産関数
		GenerateEffectProcess();

		// 生成フラグをfalseに
		generateFlag = false;
	}

}

void FireWorksEffectManeger::GenerateEffectProcess()
{
	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{

		// ランダムな値を生成
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue);
		// 値が大きすぎるので最後の補正をかけて速度に代入
		velocity = randV * LastCorrection;

		// 速度を一時保存設定
		Vector3 vel = velocity;

		//ランダムな値を渡す
		vel = vel + randV;
		// 下に落としたいのでZ軸はマイナスに
		vel.z *= -1.0f;

		// エフェクトの色の設定と向きを調整
		SelectEffectColorProcess(efectCount, vel);

		//particleを生成
		new FierWorksEffect(position, vel, crystalColor);
	}
}

void FireWorksEffectManeger::SelectEffectColorProcess(int _index,Vector3& _velocity)
{
	// いろいろな方向にいろいろな色で飛ばしたいので
	// 2の倍数の時はｘ軸方向にマイナスを掛けて色を赤に設定
	if (_index % 2 == 0)
	{
		_velocity.x *= -1.0f;
		crystalColor = CrystalColor::RED;
	}

	// 4の倍数の時はy軸方向にマイナスを掛けて色を青に設定
	if (_index % 4 == 0)
	{
		_velocity.y *= -1.0f;
		crystalColor = CrystalColor::BLUE;
	}

	// 6の倍数の時はy軸方向にマイナスを掛けて色を緑に設定
	if (_index % 6 == 0)
	{
		_velocity.y *= -1.0f;
		crystalColor = CrystalColor::GREEN;
	}

	// 8の倍数の時はｘ軸方向にマイナスを掛けて色を白に設定
	if (_index % 8 == 0)
	{
		_velocity.x *= -1.0f;
		crystalColor = CrystalColor::WHITE;
	}

}
