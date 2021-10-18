#include "AutoMoveCamera.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdlingDance.h"

AutoMoveCamera::AutoMoveCamera(const Vector3 _pos, PlayerObject* _playerObject)
	: CameraObjectBase(false, Tag::CAMERA)
{
	// メンバー変数の初期化
	SetPosition(_pos);

	forwardVec = Vector3::UnitX;
	tmpMovePos = Vector3::Zero;
	lerpObjectPos = Vector3::Zero;
	// プレイヤーのポインタを保存
	playerObject = _playerObject;
	cameraMode = CameraMode::NORMAL;
}

AutoMoveCamera::~AutoMoveCamera()
{
}

void AutoMoveCamera::UpdateGameObject(float _deltaTime)
{

	if (cameraMode == CameraMode::BEHIND)
	{
		Behind(_deltaTime);
	}
	else
	{
		InAction(_deltaTime);
	}

	// プレイヤー側に渡す前方ベクトルを生成
	forwardVec = lerpObjectPos - position;
	// 正規化
	forwardVec.Normalize();
	// Z軸を固定
	forwardVec.z = 0.0f;

	cameraMode = CameraMode::NORMAL;
}

void AutoMoveCamera::GameObjectInput(const InputState& _keyState)
{
}

void AutoMoveCamera::InAction(float _deltaTime)
{
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = playerObject->GetPosition();
	// 仮の移動ポジション変数に代入
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x -= 600.0f;
	tmpMovePos.z += 600.0f;
	tmpMovePos.y += 700.0f;
	// 仮のポジションと現在のポジションで線形補間
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);

	// 線形補間したポジションをセット
	SetPosition(position);
	Vector3 tmpViewPos = lerpObjectPos;
	//tmpViewPos.x += 200.0f;
	// 注視先がクリア用オブジェクトに変わっているのでそのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(position, tmpViewPos, Vector3::UnitZ);
	// view行列をセット
	RENDERER->SetViewMatrix(view);
}

void AutoMoveCamera::Behind(float _deltaTime)
{
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = playerObject->GetPosition();
	// 仮の移動ポジション変数に代入
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x -= 600.0f;
	tmpMovePos.z += 600.0f;
	//tmpMovePos.y += 700.0f;
	// 仮のポジションと現在のポジションで線形補間
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);

	// 線形補間したポジションをセット
	SetPosition(position);
	Vector3 tmpViewPos = lerpObjectPos;
	//tmpViewPos.x += 200.0f;
	// 注視先がクリア用オブジェクトに変わっているのでそのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(position, tmpViewPos, Vector3::UnitZ);
	// view行列をセット
	RENDERER->SetViewMatrix(view);
}
