//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateReposition.h"

/*
@fn コンストラクタ
*/
EnemyObjectStateReposition::EnemyObjectStateReposition()
	: IdlingLength(2.0f)
{
}

/*
@fn デストラクタ
*/
EnemyObjectStateReposition::~EnemyObjectStateReposition()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState EnemyObjectStateReposition::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// 追跡ターゲットがいない場合
	if (!_owner->GetIsTracking())
	{
		// 仮ポジション変数
		Vector3 tmpPosition;
		// 今のポジションと初期ポジションで線形補間を取る
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), firstPosition, _deltaTime * 1.0f);
		// ポジションをセット
		_owner->SetPosition(tmpPosition);
	}
	else // いる場合追跡状態へ
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	// 今のポジションから初期ポジションへの方向ベクトルを計算
	repositionRotationVec = firstPosition - _owner->GetPosition();
	// 初期位置までの長さを得るために変数へ保存
	Vector3 checkReposition = repositionRotationVec;
	// 正規化
	repositionRotationVec.Normalize();
	// 回転処理
	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());

	// 長さを取得
	float Length = checkReposition.Length();

	// 長さが規定値以下の場合アイドリング状態へ移行
	if (Length <= IdlingLength)
	{
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void EnemyObjectStateReposition::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_REPOSITION;
	// ステータスをActiveにする
	_owner->SetState(State::Active);

	// オーナーの移動速度を得る
	moveSpeed = _owner->GetMoveSpeed();
	// オーナーの初期ポジションを得る
	firstPosition = _owner->GetFirstPosition();
	// 今のポジションから初期ポジションへの方向ベクトルを計算
	repositionRotationVec = firstPosition - _owner->GetPosition();

	// 長さが0に近くなかったら
	if (!Math::NearZero(repositionRotationVec.Length()))
	{
		// 正規化
		repositionRotationVec.Normalize();
	}

	// 回転処理
	RotationProcess(_owner, repositionRotationVec, _owner->GetCharaForwardVec());
}
