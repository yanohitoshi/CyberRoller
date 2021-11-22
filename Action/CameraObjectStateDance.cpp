#include "CameraObjectStateDance.h"
#include "Renderer.h"
#include "PlayerObject.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return CameraState　更新終了時のステータスを返す
*/
CameraState CameraObjectStateDance::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// 回転角を自動更新
	yaw += AutomaticMoveSpeed;

	// 仮ポジション
	Vector3 tmpMovePos;
	// 追従するオブジェクトのポジション
	Vector3 lerpObjectPos;
	// 追従するオブジェクトのポインタ
	GameObject* lerpObject = _owner->GetLerpObject();
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = lerpObject->GetPosition();
	// ポジションの更新をプレイヤーが踊っている時用の半径で行う
	tmpMovePos.x = DanceRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = DanceRadius * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = lerpObjectPos.z + 600.0f;

	Vector3 setPosition;
	// 仮のポジションと現在のポジションで線形補間
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);

	// 線形補間したポジションをセット
	_owner->SetPosition(setPosition);

	// ビュー行列
	Matrix4 view;
	// 更新したポジションと追従するオブジェクトのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// 更新したview行列をセット
	RENDERER->SetViewMatrix(view);

	// 追跡対象がダンス中でなくなったら
	if (!_owner->GetLerpObject()->GetIsDancing())
	{
		// 通常状態を返す
		state = CameraState::NORMAL;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CameraObjectStateDance::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// ステータスをダンス状態に変更
	state = CameraState::DANCE;
	// ヨー変数初期化
	yaw = InitYaw;
}
