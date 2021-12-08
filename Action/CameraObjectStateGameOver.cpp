//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectStateGameOver.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return CameraState　更新終了時のステータスを返す
*/
CameraState CameraObjectStateGameOver::Update(CameraObjectBase* _owner, float _deltaTime)
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
	tmpMovePos.x = GameOverRadius * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = GameOverRadius * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = lerpObjectPos.z + OffsetZ;

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
	RENDERING_OBJECT_MANAGER->SetViewMatrix(view);

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CameraObjectStateGameOver::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// ステータスをゲームオーバー状態に変更
	state = CameraState::GAMEOVER;
	// ヨー変数初期化
	yaw = InitYaw;
}