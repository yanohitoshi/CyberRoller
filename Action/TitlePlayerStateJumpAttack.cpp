#include "TitlePlayerStateJumpAttack.h"
#include "TitlePlayerObject.h"
#include "TitleJumpAttackPlayerObject.h"
#include "SkeletalMeshComponent.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return TitlePlayerState　更新終了時のステータスを返す
*/
TitlePlayerState TitlePlayerStateJumpAttack::Update(TitlePlayerObject* _owner, float _deltaTime)
{
	// 仮ポジション変数
	Vector3 tmpPosition;
	// 線形補完をとり変数に保存
	tmpPosition = Vector3::Lerp(titleJumpAttackPlayerObject->GetPosition(), enterPosition, _deltaTime * 2.0f);
	// ポジションをセット
	titleJumpAttackPlayerObject->SetPosition(tmpPosition);

	// 回転角から定数を減算
	rotationAngle -= JumpAttackRotationAngle;
	// 回転処理
	titleJumpAttackPlayerObject->RotationProcess(rotationAngle,Vector3::UnitX);
	// フレームカウントを数える
	++frameCount;

	// ジャンプアタックの時間を過ぎていたら
	if (JumpAttackTime <= frameCount)
	{
		// オーナーに送るポジションを作る
		Vector3 sendPosition = titleJumpAttackPlayerObject->GetPosition();
		// 最初にずらした分ずらす
		sendPosition.z -= ShiftPositionZ;
		// オーナーにジャンプアタックプレイヤーのポジションを渡す
		_owner->SetPosition(sendPosition);
		// ステータスをジャンプループに変更
		state = TitlePlayerState::JUMP_LOOP;
	}

    return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void TitlePlayerStateJumpAttack::Enter(TitlePlayerObject* _owner, float _deltaTime)
{
	// stateをDEAD状態にして保存
	state = TitlePlayerState::JUMP_ATTACK;
	frameCount = 0;

	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 描画されていたら
	if (skeletalMeshComponent->GetVisible())
	{
		// 描画を切る
		skeletalMeshComponent->SetVisible(false);
	}

	// オーナーからタイトル用ジャンプアタックプレイヤーのポインタをもらう
	titleJumpAttackPlayerObject = _owner->GetTitleJumpAttackPlayerObject();
	// タイトル用ジャンプアタックプレイヤーからmeshComponentのポインタをもらう
	meshComponent = titleJumpAttackPlayerObject->GetMeshComponent();
	// 描画されていなかったら
	if (!meshComponent->GetVisible())
	{
		// 描画する
		meshComponent->SetVisible(true);
	}

	// オーナーのポジションをもらう
	enterPosition = _owner->GetPosition();
	// 高さを少しずらす
	enterPosition.z += ShiftPositionZ;
	// ジャンプアタックオブジェクトにポジションをセット
	titleJumpAttackPlayerObject->SetPosition(enterPosition);

	// オフセットを足して目標地点にする
	enterPosition.y += Offset;
}