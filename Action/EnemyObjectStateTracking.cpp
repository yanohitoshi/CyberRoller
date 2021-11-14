//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateTracking.h"

/*
@fn コンストラクタ
*/
EnemyObjectStateTracking::EnemyObjectStateTracking()
	:TrackingLengthValue(50.0f)
{
}

/*
@fn デストラクタ
*/
EnemyObjectStateTracking::~EnemyObjectStateTracking()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState EnemyObjectStateTracking::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// 追跡対象から初期ポジションへと向かうベクトルを計算
	Vector3 trackingObjectToFirstPos = firstPosition - _owner->GetAttackObjectPosition();
	// オーナーのポジションから初期ポジションへと向かうベクトルを計算
	Vector3 ownerObjectToFirstPos = firstPosition - _owner->GetPosition();

	// 追跡対象から初期ポジションへのベクトルの長さ
	float trackingObjectToFirstPosLength = trackingObjectToFirstPos.LengthSq();
	// オーナーのポジションから初期ポジションへのベクトルの長さ
	float ownerObjectToFirstPosLength = ownerObjectToFirstPos.LengthSq();

	// 追跡ターゲットがいるとき
	if (_owner->GetIsTracking())
	{
		// オーナーから追跡対象へ向かうベクトル
		trackingRotationVec = _owner->GetAttackObjectPosition() - _owner->GetPosition();
		trackingRotationVec.z = 0.0f;
		float ownerPosToTrackingObjectLength = trackingRotationVec.Length();

		// 規定値まで近づくまで追跡
		if (ownerPosToTrackingObjectLength >= TrackingLengthValue)
		{
			if (!Math::NearZero(trackingRotationVec.Length()))
			{
				trackingRotationVec.Normalize();
			}

			velocity = trackingRotationVec * moveSpeed;

			// positionに速度を足してキャラクターを動かす
			_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

			RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
		}
		else
		{
			velocity = Vector3::Zero;
			// positionに速度を足してキャラクターを動かす
			_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
		}
	}
	else if (!_owner->GetIsTracking()) // 追跡ターゲットが居なくなったとき
	{
		// 向きベクトルの長さから戻る際にターンモーションをはさむか判定
		if (ownerObjectToFirstPosLength > trackingObjectToFirstPosLength)
		{
			state = EnemyState::ENEMY_STATE_REPOSITION;
		}
		else
		{
			state = EnemyState::ENEMY_STATE_TURN;
		}
	}
	else
	{
		velocity = Vector3::Zero;
		// positionに速度を足してキャラクターを動かす
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void EnemyObjectStateTracking::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_TRACKING;
	_owner->SetState(State::Active);

	// 初期ポジションを得る
	firstPosition = _owner->GetFirstPosition();

	// 移動速度を得る
	moveSpeed = _owner->GetMoveSpeed();

	// 追跡方向を計算
	trackingRotationVec = _owner->GetAttackObjectPosition() - _owner->GetPosition();
	// 上下移動はさせないので0で固定
	trackingRotationVec.z = 0.0f;

	if (!Math::NearZero(trackingRotationVec.Length()))
	{
		// 正規化
		trackingRotationVec.Normalize();
	}

	// 回転処理
	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}
