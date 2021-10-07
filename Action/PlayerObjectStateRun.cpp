//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRun.h"
#include "SkeletalMeshComponent.h"
#include "GameObject.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateRun::PlayerObjectStateRun()
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateRun::~PlayerObjectStateRun()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateRun::Update(PlayerObject* _owner,float _deltaTime)
{

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// ジャンプフラグがfalseかつ接地状態でも無ければ
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ステータスをジャンプループにする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// 移動入力が無ければ
	if (!_owner->GetInputFlag())
	{
		// ステータスを走り終わりにする
		state = PlayerState::PLAYER_STATE_RUN_STOP;
	}

	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}
	
	// 走りながら壁に当たったら
	if (_owner->GetIsHitEnemy())
	{
		// ステータスを怯み状態にする
		state = PlayerState::PLAYER_STATE_KNOCKBACK;
	}

	ChackDeadFlag(_owner);

	ChackTimeOverFlag();

	// ownerの変数を更新
	_owner->SetMoveSpeed(moveSpeed);
	_owner->SetVelocity(velocity);

	// 更新されたstateを返す
	return state;

}

/*
@fn インプット
@brief	stateに応じて入力処理を行う
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateRun::Input(PlayerObject* _owner,const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// 移動入力処理
		GroundMove(_owner,_keyState);
	}
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN));
	// stateを走り状態にして保存
	state = PlayerState::PLAYER_STATE_RUN;

	// ownerの速度変数をもらう
	moveSpeed = _owner->GetMoveSpeed();

	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();
}
