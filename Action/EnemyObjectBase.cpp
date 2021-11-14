//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"
#include "EnemyDeadEffectManager.h"
#include "EnemyObjectStateBase.h"

/*
@fn コンストラクタ
@brief 通常のエネミーのコンストラクタ
@param	ポジション
@param	再利用するかフラグ
@param	オブジェクト判別用tag
@param	追跡対象
*/
EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, GameObject* _trackingObject)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, trackingObject(_trackingObject)
	, respawnPositionOffset(1000.0f)
	, Size(Vector3(2.0f,2.0f,2.0f))
	, BoxMin(Vector3(-30.0f, -30.0f, -10.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 60.0f))
{
	// メンバー変数初期化
	SetPosition(_pos);
	tag = _objectTag;
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	isVisible = true;
	defeatedObjectPosition = Vector3::Zero;
	attackObjectPosition = Vector3::Zero;
	// 死亡時のエフェクトを付与
	new EnemyDeadEffectManager(this);
}

/*
@fn コンストラクタ
@brief 移動するエネミーのコンストラクタ
@param	ポジション
@param	再利用するかフラグ
@param	オブジェクト判別用tag
@param	移動速度
@param	移動方向
@param	移動距離
*/
EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, GameObject* _trackingObject, MoveEnemyData _moveEnemyData)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, trackingObject(_trackingObject)
	, moveDirection(_moveEnemyData.direction)
	, moveDistance(_moveEnemyData.distance)
	, moveSpeed(_moveEnemyData.speed)
	, moveEnemyTag(_moveEnemyData.tag)
	, respawnPositionOffset(1000.0f)
	, Size(Vector3(2.0f, 2.0f, 2.0f))
	, BoxMin(Vector3(-30.0f, -30.0f, -10.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 60.0f))
{
	// メンバー変数初期化
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	defeatedObjectPosition = Vector3::Zero;
	attackObjectPosition = Vector3::Zero;
	isVisible = true;

	// 死亡時のエフェクトを付与
	new EnemyDeadEffectManager(this);
}

/*
@fn コンストラクタ
@brief 移動するエネミーのコンストラクタ
@param	ポジション
@param	再利用するかフラグ
@param	オブジェクト判別用tag
@param	移動速度
@param	追跡対象
*/
EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, moveSpeed(_moveSpeed)
	, trackingObject(_trackingObject)
	, respawnPositionOffset(1000.0f)
	, BoxMin(Vector3(-30.0f, -30.0f, -10.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 60.0f))
	, Size(Vector3(2.0f, 2.0f, 2.0f))
{
	// メンバー変数初期化
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	defeatedObjectPosition = Vector3::Zero;
	attackObjectPosition = Vector3::Zero;
	isVisible = true;

	// 死亡時のエフェクトを付与
	new EnemyDeadEffectManager(this);
}

/*
@brief ステートプール用マップにステートクラスを追加する関数
@param	_state 追加するステートクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void EnemyObjectBase::AddStatePoolMap(EnemyObjectStateBase* _state, EnemyState _stateTag)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto stateMaps = statePoolMap.find(_stateTag);

	//あるとき
	if (stateMaps != statePoolMap.end())
	{
		return;
	}
	else //ないとき
	{
		statePoolMap[_stateTag] = _state;
	}
}

/*
@brief ステートプール用マップからステートクラスを削除する関数
@param	_stateTag 鍵となるタグ
*/
void EnemyObjectBase::RemoveStatePoolMap(EnemyState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief ステートプール用マップをクリアする
*/
void EnemyObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
}

/*
@fn Animationのgetter関数
@param _state 現在のエネミーのステータス
@return Animation Animationクラスのポインタを返す
*/
const Animation* EnemyObjectBase::GetAnimation(EnemyState _state)
{
	// _state番目のアニメーションを返す
	return animTypes[static_cast<unsigned int>(_state)];
}
