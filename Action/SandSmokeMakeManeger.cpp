//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SandSmokeMakeManeger.h"
#include "ParticleEffectBase.h"
#include "SandSmokeParticle.h"

/*
@fn コンストラクタ
@param	親クラスのポインタ
*/
SandSmokeMakeManeger::SandSmokeMakeManeger(GameObject* _owner)
	:GameObject(false,Tag::PARTICLE)
	, ShiftPositionX(40.0f)
	, MaxShiftPositionY(1500.0f)
	, MinShiftPositionY(900.0f)
	, BigWallSize(1500.0f)
	, SmallWallSize(1100.0f)
	, RandValueX(500)
	, BigRandValueY(40000)
	, SmallRandValueY(20000)
	, RandValueZ(100)
	, CorrectionRandValue(10.0f)
	, GenerateFrequency(3)
	, SmallWallMaxEffect(10)
	, BigWallMaxEffect(20)
	, LastCorrection(0.1f)
	, LowestVelValue(Vector3(-2.0f,0.0f,1.0f))
{
	// メンバー変数の初期化
	owner = _owner;
	position = owner->GetPosition();
	ownerSize = owner->GetScaleVec();
	frameCount = 0;
	isBigWall = false;

	// 中心に設置するために少しずらす
	position.x -= ShiftPositionX;

	// ownerの大きさを見てそれぞれの数値分ずらして中心に設置
	// 小さいサイズの時
	if (ownerSize.y == SmallWallSize)
	{
		position.y -= MinShiftPositionY;
	}
	// 大きいサイズの時
	if (ownerSize.y == BigWallSize)
	{
		position.y -= MaxShiftPositionY;
		isBigWall = true;
	}
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
SandSmokeMakeManeger::~SandSmokeMakeManeger()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void SandSmokeMakeManeger::UpdateGameObject(float _deltaTime)
{
	// ownerの速度を見て動いている時
	if (owner->GetVelocity().z != 0)
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// パーティクルを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// ステータス状態を見る
	switch (particleState)
	{
		// 無効状態だったらbreak
	case (PARTICLE_DISABLE):
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// フレームカウントを数える
		++frameCount;

		// 小さいサイズの時
		if (isBigWall)
		{
			// アクティブ時に行う処理
			ActiveBigWallEffectProcess();
		}
		else
		{
			// アクティブ時に行う処理
			ActiveSmallWallEffectProcess();
		}

		break;
	}
}

/*
@fn 大きい壁のエフェクトがアクティブの時の処理関数
*/
void SandSmokeMakeManeger::ActiveBigWallEffectProcess()
{
	// 3フレームに一度
	if (frameCount % GenerateFrequency == 0)
	{
		GenerateWallEffectProcess(BigWallMaxEffect, BigRandValueY);
	}
}

/*
@fn 小さい壁のエフェクトがアクティブの時の処理関数
*/
void SandSmokeMakeManeger::ActiveSmallWallEffectProcess()
{
	// 3フレームに一度
	if (frameCount % GenerateFrequency == 0)
	{
		GenerateWallEffectProcess(SmallWallMaxEffect, SmallRandValueY);
	}
}

/*
@fn 動く壁のエフェクトを生成するの処理
@param _maxEffect 最大エフェクト数
@param _randYValue Y軸のランダムの値
*/
void SandSmokeMakeManeger::GenerateWallEffectProcess(const int _maxEffect, const int _randYValue)
{
	// エフェクトを10個生成
	for (int efectCount = 0; efectCount < _maxEffect; efectCount++)
	{
		// ランダムな値を生成
		Vector3 randV((rand() % RandValueX) / CorrectionRandValue, (rand() % _randYValue) / CorrectionRandValue, (rand() % RandValueZ) / CorrectionRandValue);

		// ランダムで出た値に補正をかける
		velocity = randV * LastCorrection;

		// ランダムの値に速度の最低値を追加
		velocity.x += LowestVelValue.x;
		velocity.y += LowestVelValue.y;
		velocity.z += LowestVelValue.z;

		//発生位置を設定
		Vector3 pos = position;
		//ランダムな値を渡す
		pos = pos + randV;
		//particleを生成
		new SandSmokeParticle(pos, velocity);
	}
}