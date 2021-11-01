#include "CameraObjectStateSceneClear.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateSceneClear::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// 回転角を自動更新
	yaw += AutomaticMoveSpeed;

	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = _owner->GetLerpObjectPos();
	// ポジションの更新をプレイヤーが踊っている時用の半径で行う
	tmpMovePos.x = GameClearRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = GameClearRadius * sinf(yaw) + lerpObjectPos.y;

	++trackingCount;
	if (trackingCount <=TrackingTime)
	{
		tmpMovePos.z = lerpObjectPos.z - 400.0f;
		stopPisitionZ = tmpMovePos.z;
	}
	else
	{
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
	RENDERER->SetViewMatrix(view);

	return state;
}

void CameraObjectStateSceneClear::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::SCENECLEAR;
	yaw = 0.0f;
	trackingCount = 0;
	stopPisitionZ = 0.0f;
}
