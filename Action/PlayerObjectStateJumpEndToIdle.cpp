//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpEndToIdle.h"
#include "SkeletalMeshComponent.h"
#include "SoundEffectComponent.h"

/*
@fn コンストラクタ
@param _owner 親クラスのポインタ
*/
PlayerObjectStateJumpEndToIdle::PlayerObjectStateJumpEndToIdle(PlayerObject* _owner)
{
	soundEffect = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Player/Jump.wav");
}

/*
@fn デストラクタ
*/
PlayerObjectStateJumpEndToIdle::~PlayerObjectStateJumpEndToIdle()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return PlayerState　更新終了時のステータスを返す
*/
PlayerState PlayerObjectStateJumpEndToIdle::Update(PlayerObject* _owner, float _deltaTime)
{

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// ステータスを待機状態にする
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// 移動入力があれば
	if (_owner->GetInputFlag())
	{
		// ステータスを走り出し状態にする
		state = PlayerState::PLAYER_STATE_RUN_START;
	}

	// 死亡状態チェック
	CheckDeadFlag(_owner);
	// 時間切れチェック
	CheckTimeOverFlag();

	// ownerに速度をセット
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
void PlayerObjectStateJumpEndToIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// state変更の可能性のある入力のチェック
		CheckInput(_owner, _keyState);
	}
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateJumpEndToIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE));
	// stateを待機状態にして保存
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;

	// ジャンプ力をセットする
	_owner->SetJumpPower(_owner->GetFirstJumpPower());

	// 着地状態になったのでジャンプ利用可能フラグをtrueにセット
	_owner->SetIsAvailableJumpKey(true);

	// ジャンプフラグをfalseにセット
	_owner->SetJumpFlag(false);
	_owner->SetSwitchJumpFlag(false);

	// ジャンプ攻撃系フラグ初期化
	_owner->SetIsJumpAttck(false);
	_owner->SetIsAvailableJumpAttck(true);

	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();

	// サウンドエフェクトを鳴らす
	soundEffect->Play();
}