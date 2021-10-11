//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitleGroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"

/*
@fn コンストラクタ
@param	ポジション
@param	playerのポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
*/
TitleGroundObject::TitleGroundObject(const Vector3& _p, const Vector3& _size, const Vector3& _playerPos, const Tag& _objectTag) :
	GroundObject(_p ,_size , _objectTag)
	, targetPos(_playerPos)
	, InitVelocity(Vector3(0.0f, -400.0f, 0.0f))
	, ShiftGoalAndInitPosition(1000.0f)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	goalPos = Vector3(position.x, position.y - ShiftGoalAndInitPosition, position.z);
	initPos = Vector3(position.x, position.y + ShiftGoalAndInitPosition, position.z);
	velocity = InitVelocity;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TitleGroundObject::~TitleGroundObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TitleGroundObject::UpdateGameObject(float _deltaTime)
{
	// ポジションに速度を足す
	position += velocity * _deltaTime;
	// ポジションを更新
	SetPosition(position);

	// 指定位置までオブジェクトが動いていたら
	if (position.y <= goalPos.y)
	{
		// リポジション用フラグをtrueに
		rePositionFlag = true;
	}

	// リポジション用フラグがtrueだったら
	if (rePositionFlag == true)
	{
		// ポジションに初期ポジションをセット
		position = initPos;
		// ポジションを更新
		SetPosition(position);
		// リポジション用フラグをfalseに
		rePositionFlag = false;
	}
	
}