//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectStateNormal.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return CameraState　更新終了時のステータスを返す
*/
CameraState CameraObjectStateNormal::Update(CameraObjectBase* _owner, float _deltaTime)
{
	// 仮ポジション
	Vector3 tmpMovePos;
	// 追従するオブジェクトのポジション
	Vector3 lerpObjectPos;
	// 追従するオブジェクトのポインタ
	GameObject* lerpObject = _owner->GetLerpObject();
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = lerpObject->GetPosition();
	// 仮の移動ポジション変数に代入
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x += offsetPosition.x;
	tmpMovePos.z += offsetPosition.z;

	Vector3 setPosition;
	// 仮のポジションと現在のポジションで線形補間
	setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);

	// 線形補間したポジションをセット
	_owner->SetPosition(setPosition);

	Matrix4 view;
	// 注視先がクリア用オブジェクトに変わっているのでそのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// view行列をセット
	RENDERING_OBJECT_MANAGER->SetViewMatrix(view);

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

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CameraObjectStateNormal::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// ステータスを通常状態に変更
	state = CameraState::NORMAL;
	// 追従するオブジェクトとの間隔を取得
	offsetPosition = _owner->GetOffsetPosition();
}
