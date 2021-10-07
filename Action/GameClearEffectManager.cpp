//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameClearEffectManager.h"
#include "GameClearEffect.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
GameClearEffectManager::GameClearEffectManager(GameObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, SecondCorrectionValue(5.0f)
	, CorrectionRandValue(10.0f)
	, RandValue(300)
	, MaxEffects(10)
	, MaxGenerateCount(8)
	, GenerateHeight(5500.0f)
	, GenerateFrequency(15)
	, LastCorrection(0.1f)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	frameCount = 0;
	generateCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
GameClearEffectManager::~GameClearEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void GameClearEffectManager::UpdateGameObject(float _deltaTime)
{
	// ownerの速度を見てZ軸上で動いていてかつownerの高さが一定値以上になったらACTIVEにする
	if (owner->GetVelocity().z != 0 && owner->GetPosition().z >= GenerateHeight)
	{
		// particleを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleを無効化
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

/*
@fn エフェクトがアクティブ時の処理関数
*/
void GameClearEffectManager::ActiveEffectProcess()
{
	// フレームカウントを数える
	++frameCount;
	// ownerのポジションを得る
	position = owner->GetPosition();

	// フレームカウントが15の倍数の時かつ生成カウントが8以下の時
	if (frameCount % GenerateFrequency == 0 && generateCount <= MaxGenerateCount)
	{
		// エフェクトの生産処理
		GenerateEffectProcess();

		// 1ループ終わってからカウント追加
		++generateCount;
	}
}

/*
@fn エフェクト生産処理関数
*/
void GameClearEffectManager::GenerateEffectProcess()
{
	// 10個のエフェクトを生成
	for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
	{
		// ランダムな値を生成
		Vector3 randV((rand() % RandValue) / CorrectionRandValue - SecondCorrectionValue, (rand() % RandValue) / CorrectionRandValue - SecondCorrectionValue, 0);
		// 値が大きすぎるので最後の補正をかけて速度に代入
		velocity = randV * LastCorrection;
		// 速度を一時保存設定
		Vector3 vel = velocity;

		//ランダムな値を渡す
		vel = vel + randV;
		// 散った後下に落としたいのでマイナスを掛ける
		vel.z *= -1.0f;

		CalculatingDirectionProcess(efectCount, vel);

		//particleを生成
		new GameClearEffect(position, vel);
	}

}

/*
@fn エフェクトを飛ばす方向計算処理関数
@param _index何個目のエフェクトか
@param _velocity 速度
*/
void GameClearEffectManager::CalculatingDirectionProcess(int _index, Vector3& _velocity)
{
	// いろいろな方向に飛ばしたいため
	// 2・3の倍数の際速度ベクトルをそれぞれｘもしくはｙを逆方向に変換
	// 2の倍数の時はｘ、3の倍数の時はｙ
	if (_index % 2 == 0)
	{
		_velocity.x *= -1.0f;
	}
	else if (_index % 3 == 0)
	{
		_velocity.y *= -1.0f;
	}

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