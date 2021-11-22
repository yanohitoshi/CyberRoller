//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "AutoMoveCamera.h"
#include "Renderer.h"
#include "CameraObjectStateBase.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdlingDance.h"
#include "CameraObjectStateNormal.h"
#include "CameraObjectStateChangeMode.h"
#include "CameraObjectStateDance.h"
#include "CameraObjectStateGameOver.h"
#include "CameraObjectStateSceneClear.h"
#include "CameraObjectStateSceneStart.h"

/*
@brief	コンストラクタ
@param	ポジション
@param	プレイヤーのポインタ
*/
AutoMoveCamera::AutoMoveCamera(const Vector3 _pos, PlayerObject* _playerObject)
	: CameraObjectBase(false, Tag::CAMERA)
	, NormalOffset(Vector3(-600.0f, 0.0f, 500.0f))
{
	// メンバー変数の初期化
	SetPosition(_pos);

	forwardVec = Vector3::UnitX;
	tmpMovePos = Vector3::Zero;
	lerpObjectPos = Vector3::Zero;
	offSetPosition = NormalOffset;
	// プレイヤーのポインタを保存
	playerObject = _playerObject;

	AddStatePoolMap(new CameraObjectStateNormal(), CameraState::NORMAL);
	AddStatePoolMap(new CameraObjectStateChangeMode(), CameraState::CHANGEMODE);
	AddStatePoolMap(new CameraObjectStateDance(), CameraState::DANCE);
	AddStatePoolMap(new CameraObjectStateGameOver(), CameraState::GAMEOVER);
	AddStatePoolMap(new CameraObjectStateSceneClear(), CameraState::SCENECLEAR);
	AddStatePoolMap(new CameraObjectStateSceneStart(), CameraState::SCENESTART);

	nowState = CameraState::NONE;
	nextState = CameraState::NORMAL;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
AutoMoveCamera::~AutoMoveCamera()
{
	RemoveStatePoolMap(CameraState::NORMAL);
	RemoveStatePoolMap(CameraState::CHANGEMODE);
	RemoveStatePoolMap(CameraState::DANCE);
	RemoveStatePoolMap(CameraState::GAMEOVER);
	RemoveStatePoolMap(CameraState::SCENECLEAR);
	ClearStatePoolMap();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void AutoMoveCamera::UpdateGameObject(float _deltaTime)
{
	// プレイヤーがダンス状態だったら
	if (playerObject->GetIsDancing())
	{
		// ダンスカメラに変更
		nextState = CameraState::DANCE;
	}

	if (CountDownFont::GetTimeOverFlag())
	{
		// ゲームオーバーカメラに変更
		nextState = CameraState::GAMEOVER;
	}

	if (playerObject->GetClearFlag())
	{
		// ゲームオーバーカメラに変更
		nextState = CameraState::SCENECLEAR;
	}

	// ステート外部からステート変更があったか？
	if (nowState != nextState)
	{
		//マップの中に追加するアクターのコンテナがあるかどうかを調べる
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// ステート実行
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		nextState = statePoolMap[nowState]->Update(this, _deltaTime);
	}

	// ステート内部からステート変更あったか？
	if (nowState != nextState)
	{
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}
		nowState = nextState;
	}

	nextState = CameraState::NORMAL;
	offSetPosition = NormalOffset;
}

/*
@fn 入力を引数で受け取る更新関数
@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 入力情報
*/
void AutoMoveCamera::GameObjectInput(const InputState& _keyState)
{
}