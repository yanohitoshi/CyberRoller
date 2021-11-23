//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FallExplosionArea.h"
#include "FallExplosionObject.h"
#include "BoxCollider.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクト判別用tag
@param	エリアの広さ
@param	爆発物の数
*/
FallExplosionArea::FallExplosionArea(const Vector3& _pos, const Tag _objectTag,Vector3& _area, int _quantity)
	: GameObject(false, _objectTag)
	, area(Vector3::Zero)
{
	position = _pos;
	SetPosition(position);
	quantity = _quantity;
	isFallStart = false;
	area = _area;
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::FALL_BOMB_AREA_TAG, GetOnCollisionFunc());
	AABB aabb = { _area * -1.0f,_area };
	boxCollider->SetObjectBox(aabb);

	fallExplosionObjects.resize(quantity);

	// このエリアに降る個数爆発物を生成
	for (int i = 0; i < quantity; i++)
	{
		fallExplosionObjects[i] = new FallExplosionObject(this, position, Tag::FALL_BOMB);
	}

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
FallExplosionArea::~FallExplosionArea()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void FallExplosionArea::UpdateGameObject(float _deltaTime)
{
	// もし降る状態だったら降らない状態に変更
	if (isFallStart)
	{
		isFallStart = false;
	}
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void FallExplosionArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// プレイヤーに当たったら爆発物を降る状態に変更
	if (_physicsTag == PhysicsTag::PLAYER_TAG)
	{
		isFallStart = true;
	}
}