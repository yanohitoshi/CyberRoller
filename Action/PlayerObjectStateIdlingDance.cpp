//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateIdlingDance.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

// staticメンバーを初期化
bool PlayerObjectStateIdlingDance::isDancing = false;

/*
@fn コンストラクタ
*/
PlayerObjectStateIdlingDance::PlayerObjectStateIdlingDance()
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateIdlingDance::~PlayerObjectStateIdlingDance()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateIdlingDance::Update(PlayerObject* _owner, float _deltaTime)
{
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// ジャンプ状態でなく接地状態でも無ければ
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ステータスをジャンプループ状態にする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
		// 空中でダンスしないようにダンスフラグをfalseに変更
		isDancing = false;
	}
	else if (_owner->GetInputFlag()) // 移動入力があれば
	{
		// ステータスを走り出し状態にする
		state = PlayerState::PLAYER_STATE_RUN_START;
		// 空中でダンスしないようにダンスフラグをfalseに変更
		isDancing = false;
	}
	else if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag()) // ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
		// 空中でダンスしないようにダンスフラグをfalseに変更
		isDancing = false;
	}

	// 死亡フラグが立っていたら
	if (_owner->GetDeadFlag())
	{
		// ステータスを死亡状態開始にする
		state = PlayerState::PLAYER_STATE_DEAD;
		// 空中でダンスしないようにダンスフラグをfalseに変更
		isDancing = false;
	}

	// タイムオーバーになったら
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// ステータスをコンティニュー選択開始状態にする
		state = PlayerState::PLAYER_STATE_DOWNSTART;
		// 空中でダンスしないようにダンスフラグをfalseに変更
		isDancing = false;
	}

	// 更新されたstateを返す
	return state;
}

/*
@fn インプット
@brief	stateに応じて入力処理を行う
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateIdlingDance::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// state変更の可能性のある入力のチェック
		ChackInput(_owner, _keyState);
	}
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateIdlingDance::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE_DANCE));
	// stateをダンス状態にして保存
	state = PlayerState::PLAYER_STATE_IDLE_DANCE;
	// ダンスフラグをtrueにセット
	isDancing = true;
}
