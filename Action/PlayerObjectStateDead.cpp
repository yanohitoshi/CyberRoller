//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDead.h"
#include "SkeletalMeshComponent.h"
#include "SoundEffectComponent.h"
/*
@fn コンストラクタ
*/
PlayerObjectStateDead::PlayerObjectStateDead(PlayerObject* _owner)
	: RespawnTime(120)
{
	soundEffect = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Player/Down.wav");
}

/*
@fn デストラクタ
*/
PlayerObjectStateDead::~PlayerObjectStateDead()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateDead::Update(PlayerObject* _owner, float _deltaTime)
{
	// リスポーンに移行するフラグがfalseだったら
	if (_owner->GetRespawnFlag() == false)
	{
		// 復帰までのカウント処理
		ToRespawnCountProcess(_owner);
	}

	if (_owner->GetRespawnFlag()) 	// リスポーンに移行するフラグがtrueだったら
	{
		// ステータスをリスポーンに変更する
		state = PlayerState::PLAYER_STATE_RESPAWN;
	}

	// 更新されたstateを返す
	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateDead::Enter(PlayerObject* _owner, float _deltaTime)
{

	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();

	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DEAD));

	// stateをDEAD状態にして保存
	state = PlayerState::PLAYER_STATE_DEAD;

	// リスポーンまでのカウントを初期化
	respawnCount = 0;

	// 入力可能フラグをfalseにセット
	_owner->SetIsAvailableInput(false);

	soundEffect->Play();
}

/*
@fn 復帰遷移カウント処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateDead::ToRespawnCountProcess(PlayerObject* _owner)
{
	// リスポーンするまでの時間をカウントする
	++respawnCount;
	// カウントが定数値に到達したら
	if (respawnCount >= RespawnTime)
	{
		// リスポーンに移行するフラグをfalseに 
		_owner->SetRespawnFlag(true);
		// ownerにリスポーンするポジションを渡す
		_owner->SetPosition(_owner->GetRespownPos());
		// 死亡状態フラグをfalseに
		_owner->SetDeadFlag(false);
	}
}
