//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "Renderer.h"
#include "PlayerObject.h"


TitlePlayerObject::TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, Gravity (400.0f)
	, MaxFallSpeed(-200.0f)
	, JumpDelayTime(120)
	, JumpSpeed(15.0f)
	, JumpLimitTime(13)
	, OnGroundCoordinate(100.0f)
	, RotationAngle(90.0f)
{

	// ポジションをセット
	SetPosition(_pos);

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/PlayerModel/SK_Rob.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Player/PlayerModel/SK_Rob.gpskel"));

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(TitleAnimState::ITEMNUM);
	//アニメーションを読み込み
	animTypes[IDLE] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Happy_Idle_Anim.gpanim", true);
	animTypes[RUN] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Running.gpanim", true);
	animTypes[JUMPLOOP] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Floating.gpanim", true);
	animTypes[JUMPSTART] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Jump_up.gpanim", false);
	animTypes[JUMPEND] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Landing.gpanim", false);

	//anim変数を速度0.5fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);

	// メンバー変数初期化
	firstJumpPower = 40.0f;
	jumpPower = firstJumpPower;

	RotationProcess();

}

TitlePlayerObject::~TitlePlayerObject()
{

}

void TitlePlayerObject::UpdateGameObject(float _deltaTime)
{
	// Rendererにポジションを送る
	RENDERER->SetPlayerPositon(position);

	// アニメーション状態の更新
	AnimationUpdate();


	//ジャンプ中もしくは落下中の時重力をかける（一定数以上かかったら止めて定数にする）
	if (onGround == false )
	{
		GravityProcess(_deltaTime);
	}

	// 接地状態でかつジャンプ中で無かったら
	if (onGround == true && jumpFlag == false)
	{
		JumpDelayProcess();
	}

	// ジャンプ中だったら
	if(jumpFlag == true)
	{
		JumpProcess();
	}

	// ポジションに速度を追加
	position = position + velocity * _deltaTime;
	// ポジションを更新
	SetPosition(position);

	// 接地判定処理
	IsGroundingProcess();

}

void TitlePlayerObject::RotationProcess()
{
	//Z軸を90度回転させる
	float radian = Math::ToRadians(RotationAngle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

void TitlePlayerObject::GravityProcess(float _deltaTime)
{
	// 重力を掛ける
	velocity.z -= Gravity * _deltaTime;

	// 落下速度が規定値を超えていたら
	if (velocity.z <= MaxFallSpeed)
	{
		// 落下速度を規定値に固定する
		velocity.z = MaxFallSpeed;
	}
}

void TitlePlayerObject::JumpDelayProcess()
{
	// ジャンプする間隔を数える
	++jumpDelayCount;

	// 時間が来たらジャンプさせジャンプ開始アニメーションを再生
	if (jumpDelayCount >= JumpDelayTime)
	{
		// ジャンプフラグをtrueに
		jumpFlag = true;
		// アニメーション再生
		skeltalMeshComponent->PlayAnimation(animTypes[JUMPSTART], 1.0f);
		// ステータスをJUMPSTARTに変更
		animState = JUMPSTART;
		// カウントリセット
		jumpDelayCount = 0;
	}
}

void TitlePlayerObject::JumpProcess()
{
	// ジャンプ力を追加
	velocity.z = jumpPower;

	// ジャンプ中のカウントを数える
	++jumpFrameCount;

	// ジャンプ中のカウントが規定値以下だったら
	if (jumpFrameCount > 0 && jumpFrameCount < JumpLimitTime)
	{
		// さらにジャンプ力を追加
		jumpPower += JumpSpeed;
	}
	else // ジャンプ中のカウントが規定値以上だったら
	{
		// ジャンプ力を初期に戻す
		jumpPower = firstJumpPower;
		// カウントリセット
		jumpFrameCount = 0;
		// ジャンプフラグをfalseに
		jumpFlag = false;
	}
}

void TitlePlayerObject::IsGroundingProcess()
{
	// 当たり判定で設置を取っていないので座標で判定
	// 座標が規定値以下だったら
	if (position.z <= OnGroundCoordinate)
	{
		// 接地状態にする
		onGround = true;
		// Z軸の速度を0に初期化
		velocity.z = 0.0f;
	}
	else 	// 座標が規定値以上だったら
	{
		// 接地フラグをfalseに
		onGround = false;
	}
}

void TitlePlayerObject::AnimationUpdate()
{
	// 接地中で無かったら
	if (onGround == false)
	{
		// アニメーションの再生が終わっていたら
		if (!skeltalMeshComponent->IsPlaying())
		{
			// ジャンプループアニメーションの再生を開始
			skeltalMeshComponent->PlayAnimation(animTypes[JUMPLOOP], 1.0f);
			// ステータスをJUMPLOOPに変更
			animState = JUMPLOOP;
		}

		return;
	}

	// 接地中でなくアニメーションステータスがRUNで無かったら
	if (jumpFlag == false && animState != RUN)
	{
		// ランアニメーションの再生を開始
		skeltalMeshComponent->PlayAnimation(animTypes[RUN], 1.0f);
		// ステータスをRUNに変更
		animState = RUN;
		return;
	}

}
