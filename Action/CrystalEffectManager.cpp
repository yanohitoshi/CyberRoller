//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CrystalEffectManager.h"
#include "CrystalDefaultEffect.h"
#include "PlayerObject.h"
#include "MoveWallBlock.h"

/*
@fn コンストラクタ
@param	親クラスのポインタ
@param	何色か判定用Tag
@param シーン最後の動く壁のポインタ
*/
CrystalEffectManager::CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor, MoveWallBlock* _lastMoveWall)
	:GameObject(false, Tag::PARTICLE)
	, ShiftPositionZ(100.0f)
	, Radius(150.0f)
	, YawSpeed(0.06f)
	, SecondCorrectionValue(2.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(100)
	, DeltaTimeCorrectionValue(10.0f)
	, LastCorrection(0.1f)
	, lastMoveWallBlock(_lastMoveWall)
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
	isEffectActive = false;

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

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CrystalEffectManager::~CrystalEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CrystalEffectManager::UpdateGameObject(float _deltaTime)
{
	// エフェクトを発生させない状態の時
	if (!isEffectActive)
	{
		// 最後の壁が開いているかのフラグをもらう
		//isEffectActive = lastMoveWallBlock->GetOpenFlag();
		isEffectActive = true;
	}


	// activeFrameCountが8以上になったら
	if (isEffectActive)
	{
		// particleStateを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleStateを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
		// activeFrameCountを初期化
		activeFrameCount = 0;
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
		ActiveEffectProcess(_deltaTime);
		break;
	}
}

/*
@fn エフェクトがアクティブ時の処理関数
@param	_deltaTime 前のフレームでかかった時間
*/
void CrystalEffectManager::ActiveEffectProcess(float _deltaTime)
{
	// 発生場所の回転処理
	RotationProcess(_deltaTime);

	// アクティブを制御するカウントを数える
	++activeFrameCount;

	if (activeFrameCount % 8 == 0)
	{
		GenerateEffectProcess();
	}
}

/*
@fn エフェクト生産処理関数
*/
void CrystalEffectManager::GenerateEffectProcess()
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

/*
@fn ポジションの回転処理関数
@param	_deltaTime 前のフレームでかかった時間
*/
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