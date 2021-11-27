//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectStateSceneClear.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return CameraState　更新終了時のステータスを返す
*/
CameraState CameraObjectStateSceneClear::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// 回転角を自動更新
	yaw += AutomaticMoveSpeed;

	// 仮の移動先ポジション
	Vector3 tmpMovePos;
	// 追従するオブジェクトのポジション
	Vector3 lerpObjectPos;
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = _owner->GetLerpObjectPos();
	// ポジションの更新をプレイヤーが踊っている時用の半径で行う
	tmpMovePos.x = GameClearRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = GameClearRadius * sinf(yaw) + lerpObjectPos.y;

	// 追跡する時間をカウント
	++trackingCount;

	// 追跡時間内だったら
	if (trackingCount <=TrackingTime)
	{
		// 追跡する
		tmpMovePos.z = lerpObjectPos.z - OffsetZ;
		stopPisitionZ = tmpMovePos.z;
	}
	else
	{
		// その場で停止
		tmpMovePos.z = stopPisitionZ;
	}

	Vector3 setPosition;
	// 仮のポジションと現在のポジションで線形補間
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);

	// 線形補間したポジションをセット
	_owner->SetPosition(setPosition);

	Matrix4 view;
	// 更新したポジションと追従するオブジェクトのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// 更新したview行列をセット
	RENDERING_OBJECT_MANAGER->SetViewMatrix(view);

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CameraObjectStateSceneClear::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// ステータスをシーンクリア状態に変更
	state = CameraState::SCENECLEAR;
	// 変数初期化
	yaw = InitYaw;
	trackingCount = 0;
	stopPisitionZ = 0.0f;
}