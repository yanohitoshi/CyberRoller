#include "CrystalEffectManager.h"
#include "CrystalDefaultEffect.h"


CrystalEffectManager::CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor)
	:GameObject(false, Tag::PARTICLE)
	, ShiftPositionZ(100.0f)
	, Radius(150.0f)
	, YawSpeed(0.06f)
	, SecondCorrectionValue(2.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, DeltaTimeCorrectionValue(10.0f)
	, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	crystalColor = _crystalColor;
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = owner->GetPosition();
	position.z -= ShiftPositionZ;
	frameCount = 0;
	activeFrameCount = 0;
	tmpMovePos = Vector3::Zero;

	// 色ごとにマネージャークラスを生成するためそれぞれに場合分けし初期化
	if (crystalColor == CrystalColor::WHITE)
	{
		// 初期角度を設定
		yaw = Math::ToRadians(0);
	}
	else if (crystalColor == CrystalColor::RED)
	{
		// 初期角度を設定
		yaw = Math::ToRadians(90);
	}
	else if (crystalColor == CrystalColor::BLUE)
	{
		// 初期角度を設定
		yaw = Math::ToRadians(180);
	}
	else if (crystalColor == CrystalColor::GREEN)
	{
		// 初期角度を設定
		yaw = Math::ToRadians(270);
	}
}

CrystalEffectManager::~CrystalEffectManager()
{
}

void CrystalEffectManager::UpdateGameObject(float _deltaTime)
{

	RotationProcess(_deltaTime);

	// アクティブを制御するカウントを数える
	++activeFrameCount;

	// activeFrameCountが8以上になったら
	if (activeFrameCount  >= 8)
	{
		// particleStateを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
		// activeFrameCountを初期化
		activeFrameCount = 0;
	}
	else
	{
		// particleStateを無効化
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

		// エフェクト生成
		CreateEffect();

		break;

	}

}

void CrystalEffectManager::CreateEffect()
{
	// 速度を一時保存する変数
	Vector3 vel;
	// 速度用のランダムな値を生成※x軸とy軸の速度は0.0fに固定
	Vector3 randV(0.0f, 0.0f, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);
	// 値が大きすぎるので最後の補正をかけて速度に代入
	velocity = randV * LastCorrection;
	//速度を設定
	vel = velocity + randV;

	// ポジション用のランダムな値を取る
	Vector3 randPos((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);
	// 値が大きすぎるので最後の補正をかける
	Vector3 pos = randPos * LastCorrection;
	//ランダムな値を渡す
	pos = pos + position;

	//particleを生成
	new CrystalDefaultEffect(pos, vel, crystalColor);
}

void CrystalEffectManager::RotationProcess(float _deltaTime)
{
	// 回転速度を追加
	yaw += YawSpeed;

	// 回転角でxとyポジションを設定
	tmpMovePos.x = Radius * cosf(yaw) + owner->GetPosition().x;
	tmpMovePos.y = Radius * sinf(yaw) + owner->GetPosition().y;
	// z軸は固定
	tmpMovePos.z = owner->GetPosition().z - ShiftPositionZ;
	// 計算したポジションと今のポジションで線形保管を取りポジションに代入
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaTimeCorrectionValue);
	// ポジションを更新
	SetPosition(position);
}
