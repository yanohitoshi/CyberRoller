#include "PlayerObjectStateExplosionBlowAway.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateExplosionBlowAway::PlayerObjectStateExplosionBlowAway()
	: knockBackFrameCount(0)
	, KnockBackPower(20.0f)
	, KnockBackTime(10)
{
}

PlayerObjectStateExplosionBlowAway::~PlayerObjectStateExplosionBlowAway()
{
}

PlayerState PlayerObjectStateExplosionBlowAway::Update(PlayerObject* _owner, float _deltaTime)
{
	// ノックバックの時間を数える
	++knockBackFrameCount;

	// 接地中か判定
	if (!_owner->GetOnGround())
	{
		// 重力をかける
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	}

	// ノックバック時間を過ぎたら
	if (knockBackFrameCount <= KnockBackTime)
	{
		knockBackSpeed += KnockBackPower;
		// 速度を追加
		velocity += knockBackDirection * knockBackSpeed;
	}

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (_owner->GetOnGround())
	{
		velocity = Vector3::Zero;
		_owner->SetVelocity(velocity);
		// 壁に当たったフラグをfalseに
		_owner->SetIsHitExplosion(false);
		// stateをアイドリングに変更
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
	}

	CheckDeadFlag(_owner);

	CheckTimeOverFlag();

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateExplosionBlowAway::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_KNOCKBACK));
	// stateを怯み状態にして保存
	state = PlayerState::PLAYER_STATE_BLOWAWAY;

	// 速度初期化
	velocity = Vector3::Zero;
	knockBackSpeed = 50.0f;
	// カウントを初期化
	knockBackFrameCount = 0;

	// 当たったエネミーのポジションを取得
	hitEnemyPosition = _owner->GetHitKnockBackObjectPosition();
	// ノックバックする方向ベクトルを計算
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;

	if (!Math::NearZero(knockBackDirection.Length()))
	{
		// 正規化
		knockBackDirection.Normalize();
	}

	// 回転処理
	// ノックバック時動く方向と逆の方向を向かせるのでx,y軸に-1.0をかける
	RotationProcess(_owner, Vector3(knockBackDirection.x * -1.0f, knockBackDirection.y * -1.0f, 0.0f), _owner->GetCharaForwardVec());

	// 上方向ベクトルを追加
	knockBackDirection.z = 1.0f;
}
