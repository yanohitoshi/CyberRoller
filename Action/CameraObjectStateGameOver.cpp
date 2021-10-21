#include "CameraObjectStateGameOver.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateGameOver::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// 回転角を自動更新
	yaw += AutomaticMoveSpeed;

	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	GameObject* lerpObject = _owner->GetLerpObject();
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = lerpObject->GetPosition();
	// ポジションの更新をプレイヤーが踊っている時用の半径で行う
	tmpMovePos.x = GameOverRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = GameOverRadius * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = lerpObjectPos.z + 600.0f;

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

void CameraObjectStateGameOver::Input(CameraObjectBase* _owner, const InputState& _keyState)
{
}

void CameraObjectStateGameOver::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::GAMEOVER;
	yaw = 180.0f;
}
