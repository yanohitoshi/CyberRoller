//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectStateChangeMode.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return CameraState　更新終了時のステータスを返す
*/
CameraState CameraObjectStateChangeMode::Update(CameraObjectBase* _owner, float _deltaTime)
{
	++startStateCount;

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
	tmpMovePos.y += offsetPosition.y;
	tmpMovePos.z += offsetPosition.z;

	// 実際にセットするポジション
	Vector3 setPosition;

	// ゆっくり補間する時間内だったら
	if (startStateCount <= SlowLrapTime)
	{
		// 仮のポジションと現在のポジションで線形補間
		setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * SlowLrapCorrection);
	}
	else // それ以外
	{
		// 仮のポジションと現在のポジションで線形補間
		setPosition = Vector3::Lerp(_owner->GetPosition(), tmpMovePos, _deltaTime * DeltaCorrection);
	}

	// 線形補間したポジションをセット
	_owner->SetPosition(setPosition);

	// ビュー行列
	Matrix4 view;
	// 注視先がクリア用オブジェクトに変わっているのでそのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(_owner->GetPosition(), lerpObjectPos, Vector3::UnitZ);
	// view行列をセット
	RENDERING_OBJECT_MANAGER->SetViewMatrix(view);

	// 次のフレームでの前方ベクトル
	Vector3 nextForwardVec;

	// プレイヤー側に渡す前方ベクトルを生成
	nextForwardVec = lerpObjectPos - _owner->GetPosition();

	if (!Math::NearZero(nextForwardVec.Length()))
	{
		// 正規化
		nextForwardVec.Normalize();
	}

	// Z軸を固定
	nextForwardVec.z = 0.0f;

	_owner->SetCameraVec(nextForwardVec);

	// 画角切り替えフラグがfalseだったら
	if (!_owner->GetIsChangeMode())
	{
		state = CameraState::NORMAL;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void CameraObjectStateChangeMode::Enter(CameraObjectBase* _owner, float _deltaTime)
{
	// ステータスを画角変更モードに変更
	state = CameraState::CHANGEMODE;
	// 変更する画角の間隔情報をもらう
	offsetPosition = _owner->GetOffsetPosition();
	// 変数初期化
	startStateCount = 0;
}