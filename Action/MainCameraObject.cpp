//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MainCameraObject.h"
#include "CameraObjectBase.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "FirstStageScene.h"
#include "FirstStageUI.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdlingDance.h"


MainCameraObject::MainCameraObject(const Vector3 _pos, PlayerObject* _playerObject) 
	: CameraObjectBase(false,Tag::CAMERA)
	, YawSpeed(0.055f)
	, PitchSpeed(0.03f)
	, MaxPitch(70.0f)
	, MinPitch(-30.0f)
	, MaxRadius(700.0f)
	, MinRadius(10.0f)
	, DanceRadius(500.0f)
	, TimeOverRadius(400.0f)
	, MediumRadius(300.0f)
	, DeltaCorrection(8.0f)
	, AutomaticMoveSpeed(0.01f)
	, ShiftGazePoint(100.0f)
	, CorrectionBackRadius(20.f)
	, AabbInitMax(Vector3(100.0f, 100.0f, 50.0f))
	, AabbInitMin(Vector3(-100.0f, -100.0f, -50.0f))
{
	// メンバー変数の初期化
	SetPosition(_pos);
	yaw = Math::ToRadians(180);
	pitch = Math::ToRadians(30);
	radius = MaxRadius;
	height = 0.0f;
	forwardVec = Vector3::UnitX;
	tmpMovePos = Vector3::Zero;
	lerpObjectPos = Vector3::Zero;
	hitPosition = Vector3::Zero;
	hitFlag = false;
	tmpHitFlag = false;

	//当たり判定用のコンポーネントの追加と初期化
	boxcollider = new BoxCollider(this, PhysicsTag::CAMERA_TAG, GetOnCollisionFunc());
	AABB aabb = { AabbInitMin,AabbInitMax };
	boxcollider->SetObjectBox(aabb);

	// プレイヤーのポインタを保存
	playerObject = _playerObject;

}


MainCameraObject::~MainCameraObject()
{
}

void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	// プレイヤーがクリア状態でなくかつタイムオーバーでもなく踊ってもいなかったら
	if (playerObject->GetClearFlag() == false && CountDownFont::GetTimeOverFlag() == false && !PlayerObjectStateIdlingDance::GetIsDancing())
	{
		// ゲームプレイ中の移動計算処理
		InGameMovableProcess(_deltaTime);
	}
	else if (playerObject->GetClearFlag() == true) // 最終ステージをクリアしていたら
	{
		// クリア状態の処理
		GameClearProcess(_deltaTime);
	}
	else if (CountDownFont::GetTimeOverFlag() == true) // タイムオーバーになったら
	{
		// ゲームオーバー時の処理
		GameOverProcess(_deltaTime);
	}
	else if (PlayerObjectStateIdlingDance::GetIsDancing() && CountDownFont::GetTimeOverFlag() == false)
	{
		// 一定時間入力がなくプレイヤーが踊っている時の処理
		PlayerInDanceProcess(_deltaTime);
	}

}

void MainCameraObject::GameObjectInput(const InputState& _keyState)
{
	// 入力状態チェック関数
	ChackInputProcess(_keyState);

	// ピッチ補正関数
	CorrectionPitch();
}


/*
@param _offset　見たい座標との差
@param _parentPos　見る座標
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	hasParentObject = true;
	offsetPos = _offset;
	lerpObjectPos = _parentPos;
}


void MainCameraObject::InGameMovableProcess(float _deltaTime)
{
	// カメラ半径の補正関数
	CorrectionRadius();

	// ポジション計算関数
	CalculationPosition(_deltaTime);

	// ビュー行列計算関数
	CalculationViewMatrix();

	// プレイヤー側に渡す前方ベクトルを生成
	forwardVec = lerpObjectPos - position;
	// 正規化
	forwardVec.Normalize();
	// Z軸を固定
	forwardVec.z = 0.0f;

	// 当たり判定を行うオブジェクトと当たったポジションを保存
	tmpHitFlag = hitFlag;

	// 当たり判定を行う際に利用する変数の初期化
	hitPosition = Vector3::Zero;
	hitFlag = false;
}

void MainCameraObject::CorrectionRadius()
{
	// 今のフレームで当たっていて前のフレームで当たっていなければ
	if (hitFlag == true && tmpHitFlag == false)
	{
		// 当たったポジションxがマイナスだったら
		if (hitPosition.x < 0.0f)
		{
			hitPosition.x *= -1.0f;
		}

		// 当たったポジションyがマイナスだったら
		if (hitPosition.y < 0.0f)
		{
			hitPosition.y *= -1.0f;
		}

		// 当たったポジションを比べ小さい方をカメラの回転半径として採用
		if (hitPosition.x < hitPosition.y)
		{
			// 見る対象物から当たった場所を引いて長さを取る
			radius = lerpObjectPos.x - hitPosition.x;
			// そのまま使うと壁にめり込む可能性があるので少し小さくする
			radius -= CorrectionBackRadius;
		}
		else if (hitPosition.x > hitPosition.y)
		{
			// 見る対象物から当たった場所を引いて長さを取る
			radius = lerpObjectPos.y - hitPosition.y;
			// そのまま使うと壁にめり込む可能性があるので少し小さくする
			radius -= CorrectionBackRadius;
		}

		// 半径がマイナスになっていたらプラスに変換
		if (radius <= 0.0f)
		{
			radius *= -1.0f;
		}
	}
	else
	{
		// 半径を定数化
		radius = MaxRadius;
	}

	// 半径が最大値を超えていたら
	if (radius >= MaxRadius)
	{
		// 最大値を代入
		radius = MaxRadius;
	}
	else if (radius <= MinRadius) // 半径が最小値を下回っていたらいたら
	{
		// 最小値を代入
		radius = MinRadius;
	}

	// カメラの高さが0.0f以下でかつ最小値より高かったら
	if (pitch < 0.0f && pitch > MinPitch)
	{
		// 半径を小さくして追跡するオブジェクトに近づける
		radius -= MediumRadius;
	}
}

void MainCameraObject::CorrectionPitch()
{
	// ピッチが最大値を超えていたら
	if (pitch > Math::ToRadians(MaxPitch))
	{
		// 最大値を代入
		pitch = Math::ToRadians(MaxPitch);
	}
	// ピッチが最小値を下回っていたら
	if (pitch < Math::ToRadians(MinPitch))
	{
		// 最小値を代入
		pitch = Math::ToRadians(MinPitch);
	}
}

void MainCameraObject::CalculationPosition(float _deltaTime)
{
	// 回転角と半径を用いて仮のポジションを設定
	tmpMovePos.x = radius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = radius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

	// 仮のポジションと現在のポジションで線形補間
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);

	// 線形補間したポジションをセット
	SetPosition(position);
}

void MainCameraObject::CalculationViewMatrix()
{
	// 追従するオブジェクトのポジションを代入
	Vector3 viewPosition = Vector3(lerpObjectPos.x, lerpObjectPos.y, lerpObjectPos.z + ShiftGazePoint);
	// 更新したポジションと追従するオブジェクトのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(position, viewPosition, Vector3::UnitZ);
	// 更新したview行列をセット
	RENDERER->SetViewMatrix(view);
}

void MainCameraObject::GameClearProcess(float _deltaTime)
{
	// 注視先がクリア用オブジェクトに変わっているのでそのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3::UnitZ);
	// view行列をセット
	RENDERER->SetViewMatrix(view);
}

void MainCameraObject::GameOverProcess(float _deltaTime)
{
	// 回転角を自動更新
	yaw += AutomaticMoveSpeed;

	// ポジションの更新をタイムオーバー用の半径で行う
	tmpMovePos.x = TimeOverRadius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = TimeOverRadius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

	// 仮のポジションと現在のポジションで線形補間
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);
	// 線形補間したポジションをセット
	SetPosition(position);

	// 更新したポジションと追従するオブジェクトのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3::UnitZ);
	// 更新したview行列をセット
	RENDERER->SetViewMatrix(view);
}

void MainCameraObject::PlayerInDanceProcess(float _deltaTime)
{
	// 回転角を自動更新
	yaw += AutomaticMoveSpeed;

	// ポジションの更新をプレイヤーが踊っている時用の半径で行う
	tmpMovePos.x = DanceRadius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
	tmpMovePos.y = DanceRadius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
	tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

	// 仮のポジションと現在のポジションで線形補間
	position = Vector3::Lerp(position, tmpMovePos, _deltaTime * DeltaCorrection);
	// 線形補間したポジションをセット
	SetPosition(position);

	// 更新したポジションと追従するオブジェクトのポジションを用いてview行列を更新
	view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3::UnitZ);
	// 更新したview行列をセット
	RENDERER->SetViewMatrix(view);

}

void MainCameraObject::ChackInputProcess(const InputState& _keyState)
{

	// クリア状態じゃ無かったら
	if (playerObject->GetClearFlag() == false)
	{
		// 右スティックの角度を保存するベクトル変数
		Vector2 rightAxis = Vector2(0.0f, 0.0f);
		rightAxis = _keyState.Controller.GetLAxisRightVec();

		// キーボード入力と右スティックのX軸の角度を見て速度分を追加
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT) == 1 ||
			rightAxis.x > 0.0f)
		{
			yaw += YawSpeed;
		}
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT) == 1 ||
			rightAxis.x < 0.0f)
		{
			yaw -= YawSpeed;
		}
		// キーボード入力と右スティックのY軸の角度を見て速度分を追加
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_UP) == 1 ||
			rightAxis.y < 0.0f)
		{
			pitch -= PitchSpeed;
		}
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN) == 1 ||
			rightAxis.y > 0.0f)
		{
			pitch += PitchSpeed;
		}

	}

}

void MainCameraObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{	
	// ヒットした際にヒットフラグがfalseだったら
	if (hitFlag == false)
	{
		// ヒットフラグをtrueに
		hitFlag = true;
		// 当たったオブジェクトのポジションを保存 
		hitPosition = _hitObject.GetPosition();
	}

	// 押し戻し用にワールドBoxを保存
	AABB myAabb = boxcollider->GetWorldBox();

	if (_hitObject.GetisPushBackToCamera())
	{
		// 押し戻し関数を呼び出す
		FixCollision(myAabb, _hitObject.aabb);
	}

}

void MainCameraObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{
	// 速度補正ベクトル変数
	Vector3 ment = Vector3::Zero;
	// 押し戻し計算
	calcCollisionFixVec(myAABB, pairAABB, ment);
	// ポジションを更新
	SetPosition(position + ment);
}

void MainCameraObject::calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3::Zero;

	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;


	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}
