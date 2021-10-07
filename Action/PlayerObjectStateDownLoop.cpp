//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateDownLoop.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateDownLoop::PlayerObjectStateDownLoop()
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateDownLoop::~PlayerObjectStateDownLoop()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
PlayerState PlayerObjectStateDownLoop::Update(PlayerObject* _owner, float _deltaTime)
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

	// 入力フラグがtrueになった時
	if (isInput)
	{
		// 入力状態を見てコンティニュー状態を確認
		ChackContinueProcess();
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
void PlayerObjectStateDownLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// もし、コントローラーのAボタンまたはキーボードのCボタンが押されたら
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_C) == true)
	{
		// 入力フラグをtrueに変更
		isInput = true;
		// コンティニューフラグをtrueに変更
		isContinue = true;
	}
	// もし、コントローラーのBボタンまたはキーボードのZボタンが押されたら
	else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			 _keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_Z) == true)
	{
		// 入力フラグのみをtrueに変更
		isInput = true;
	}
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateDownLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_LOOP));
	// stateをダウンループ状態にして保存
	state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	// オーナーの持つ速度を取得
	velocity = _owner->GetVelocity();
	// コンティニューフラグを初期化
	isContinue = false;
	// 入力があったかどうかフラグを初期化
	isInput = false;
}

/*
@fn コンティニュー確認処理関数
*/
void PlayerObjectStateDownLoop::ChackContinueProcess()
{
	// コンティニューフラグがtrueだったら
	if (isContinue)
	{
		// コンティニューが選択された状態に変更
		state = PlayerState::PLAYER_STATE_DOWN_UP;
	}
	else // コンティニューされていなかったら
	{
		// ゲームオーバー状態に変更
		state = PlayerState::PLAYER_STATE_DOWN_OVER;
	}
}
