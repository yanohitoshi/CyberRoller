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
}

AutoMoveCamera::~AutoMoveCamera()
{
}

void AutoMoveCamera::UpdateGameObject(float _deltaTime)
{
	// 追従するオブジェクトのポジションを取得
	lerpObjectPos = playerObject->GetPosition();
	// 仮の移動ポジション変数に代入
	tmpMovePos = lerpObjectPos;
	tmpMovePos.x -= 500.0f;
	tmpMovePos.z += 500.0f;
	// 仮のポジションと現在のポジションで線形補間
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime);

	// 線形補間したポジションをセット
	SetPosition(position);

	// 注視先がクリア用オブジェクトに変わっているのでそのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3::UnitZ);
	// view行列をセット
	RENDERER->SetViewMatrix(view);

	// プレイヤー側に渡す前方ベクトルを生成
	forwardVec = lerpObjectPos - position;
	// 正規化
	forwardVec.Normalize();
	// Z軸を固定
	forwardVec.z = 0.0f;
}

void AutoMoveCamera::GameObjectInput(const InputState& _keyState)
{
}
