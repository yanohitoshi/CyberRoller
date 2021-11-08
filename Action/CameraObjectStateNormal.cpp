#include "CameraObjectStateNormal.h"
#include "Renderer.h"
#include "PlayerObject.h"

CameraState CameraObjectStateNormal::Update(CameraObjectBase* _owner, float _deltaTime)
{
	Vector3 tmpMovePos;
	Vector3 lerpObjectPos;
	GameObject* lerpObject = _owner->GetLerpObject();
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = lerpObject->GetPosition();
	// 仮の移動ポジション変数に代入
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x += offsetPosition.x + 400.0f;
	tmpMovePos.y += -200.0f;
	tmpMovePos.z += offsetPosition.z - 200.0f;

	Vector3 setPosition;
	// 仮のポジションと現在のポジションで線形補間
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);

	// 線形補間したポジションをセット
	_owner->SetPosition(setPosition);

	Matrix4 view;
	// 注視先がクリア用オブジェクトに変わっているのでそのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// view行列をセット
	RENDERER->SetViewMatrix(view);

	Vector3 nextForwardVec;
	// プレイヤー側に渡す前方ベクトルを生成
	nextForwardVec = lerpObjectPos - _owner->GetPosition();
	// 正規化
	nextForwardVec.Normalize();
	// Z軸を固定
	nextForwardVec.z = 0.0f;

	_owner->SetCameraVec(nextForwardVec);

	return state;
}

void CameraObjectStateNormal::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	state = CameraState::NORMAL;
	offsetPosition = _owner->GetOffsetPosition();
}
