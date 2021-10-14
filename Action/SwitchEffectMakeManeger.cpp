//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SwitchEffectMakeManeger.h"
#include "SwitchParticleEffect.h"

/*
@fn コンストラクタ
@param	親クラスのポインタ
*/
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
	checkOnFlag = false;
	tmpCheckOnFlag = false;
	generateFlag = false;

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
SwitchEffectMakeManeger::~SwitchEffectMakeManeger()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void SwitchEffectMakeManeger::UpdateGameObject(float _deltaTime)
{
	// ownerのフラグを保存
	checkOnFlag = owner->GetSwitchFlag();

	// 前フレームのフラグと今のフラグが違っていたら
	if (checkOnFlag != tmpCheckOnFlag)
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
		// 生成フラグをtrueに
		generateFlag = true;
	}
	
	// ステータス状態を見る
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
			ActiveEffectProcess();

			// 生成フラグをfalseに
			generateFlag = false;
		}

		// particleStateを無効化してbreak
		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}
	
	// フラグを保存
	tmpCheckOnFlag = checkOnFlag;

}

/*
@fn エフェクトがアクティブ時の処理関数
*/
void SwitchEffectMakeManeger::ActiveEffectProcess()
{
	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{
		// ランダムな値を生成
		Vector3 randV((rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue, (rand() % RandValue) / CorrectionRandValue + SecondCorrectionValue);

		// 値が大きすぎるので最後の補正をかけて速度に代入
		velocity = randV * LastCorrection;

		// 速度を一時保存
		Vector3 vel = velocity;

		//ランダムな値を渡す
		vel = vel + randV;

		CalculatingDirectionProcess(efectCount, vel);

		// ownerのポジションを代入
		position = owner->GetPosition();

		//particleを生成
		new SwitchParticleEffect(position, vel);
	}

}

/*
@fn エフェクトを飛ばす方向計算処理関数
*/
void SwitchEffectMakeManeger::CalculatingDirectionProcess(int _index, Vector3& _velocity)
{
	// 2・3の倍数の際速度ベクトルをそれぞれｘもしくはyを逆方向に変換
	// 2の倍数の時はｘ、3の倍数の時はｙ
	if (_index % 2 == 0)
	{
		_velocity.x *= -1.0f;
	}
	else if (_index % 3 == 0)
	{
		_velocity.y *= -1.0f;
	}

	// いろいろな方向に飛ばしたいため
	// 4・6の倍数の際速度ベクトルをそれぞれｘもしくはyを逆方向に変換
	// 6の倍数の時はｘ、4の倍数の時はｙ
	if (_index % 4 == 0)
	{
		_velocity.y *= -1.0f;
	}
	else if (_index % 6 == 0)
	{
		_velocity.x *= -1.0f;
	}

}