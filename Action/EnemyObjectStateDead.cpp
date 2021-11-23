//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateDead.h"

/*
@fn コンストラクタ
*/
EnemyObjectStateDead::EnemyObjectStateDead()
	: RespawnTime(200)
	, InvisibleTime(50)
	, FirstBlowAwayPower(100.0f)
	, BlowAwayPower(1.2f)
	, MaxSpeed(2000.0f)
{
}

/*
@fn デストラクタ
*/
EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// ステータスのフレーム時間を計測
	++frameCount;

	// 移動速度に吹っ飛ぶ力を足す
	moveSpeed *= BlowAwayPower;

	// 最大速度に到達していたら最大速度に固定する
	if (moveSpeed >= MaxSpeed)
	{
		moveSpeed = MaxSpeed;
	}

	// 作用する速度ベクトル計算
	velocity = blowAwayDirection * moveSpeed;

	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// 時間が来たら描画を切る
	if (frameCount >= InvisibleTime)
	{
		_owner->SetIsVisible(false);
		skeletalMeshComponent->SetVisible(false);
	}

	// 時間が来たらリスポーン
	if (frameCount >= RespawnTime)
	{
		state = EnemyState::ENEMY_STATE_RESPAWN;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void EnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_DEAD;
	// ステータスを無効状態に
	_owner->SetState(State::Disabling);
	// フレームカウント初期化
	frameCount = 0;
	// 吹っ飛ぶ方向を計算
	blowAwayDirection = _owner->GetPosition() - _owner->GetDefeatedObjectPosition();

	// 長さが0に近くなかったら
	if (!Math::NearZero(blowAwayDirection.Length()))
	{
		// 正規化
		blowAwayDirection.Normalize();
	}

	// 上下方向を0に固定
	blowAwayDirection.z = 0.0f;
	// 移動速度を初速にする
	moveSpeed = FirstBlowAwayPower;
}
