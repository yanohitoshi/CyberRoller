//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDownStart.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateDownStart::PlayerObjectStateDownStart()
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateDownStart::~PlayerObjectStateDownStart()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return PlayerState　更新終了時のステータスを返す
*/
PlayerState PlayerObjectStateDownStart::Update(PlayerObject* _owner, float _deltaTime)
{
	// 重力にデルタタイムをかけた値を代入
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	// 落下速度が規定値を超えていたら
	if (velocity.z <= MaxFallSpeed)
	{
		// 規定値に固定
		velocity.z = MaxFallSpeed;
	}

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// タイムオーバーループスタート状態のアニメーションが再生されていなかったら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// コンティニュー選択状態に変更
		state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	}

	// ownerの変数を更新
	_owner->SetVelocity(velocity);

	// 更新されたstateを返す
	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateDownStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWNSTART));
	// stateをコンティニューするか選択する状態にして保存
	state = PlayerState::PLAYER_STATE_DOWNSTART;

	// オーナーの持つ速度を取得
	velocity = _owner->GetVelocity();
	// x軸とy軸の速度を0.0fに初期化
	velocity.x = 0.0f;
	velocity.y = 0.0f;
}