//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraChangePoint.h"
#include "BoxCollider.h"
#include "CameraObjectStateBase.h"

/*
@fn コンストラクタ
@param	ポジション
@param	当たり判定用AABB
@param	変更する間隔
@param	オブジェクト判別用tag
*/
CameraChangePoint::CameraChangePoint(const Vector3& _p, const AABB& _box, Vector3& _changeOffset,const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	// ポジションの初期化
	position = _p;
	changeOffset = _changeOffset;
	// ポジションをセット
	SetPosition(position);

	// 当たり判定用ボックスコライダー付与
	boxCollider = new BoxCollider(this, PhysicsTag::CAMERA_MODE_CHANGE_AREA, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CameraChangePoint::~CameraChangePoint()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CameraChangePoint::UpdateGameObject(float _deltaTime)
{
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void CameraChangePoint::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// プレイヤーと当たったら
	if (_physicsTag == PhysicsTag::PLAYER_TAG)
	{
		mainCamera->SetNextState(CameraState::CHANGEMODE);
		mainCamera->SetOffsetPosition(changeOffset);
	}
}