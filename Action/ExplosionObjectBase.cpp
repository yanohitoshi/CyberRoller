//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectBase.h"
#include "ExplosionObjectStateBase.h"

/*
@fn コンストラクタ
@param	オブジェクト判別用tag
*/
ExplosionObjectBase::ExplosionObjectBase(const Tag _objectTag)
	: GameObject(false, _objectTag)
	, hitPosition(Vector3::Zero)
	, firstPosition(Vector3::Zero)
	, fallArea(Vector3::Zero)
	, fallSpeed(0.0f)
{
}

/*
@brief ステートプール用マップにステートクラスを追加する関数
@param	_state 追加するステートクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void ExplosionObjectBase::AddStatePoolMap(ExplosionObjectStateBase* _state, ExplosionObjectState _stateTag)
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
void ExplosionObjectBase::RemoveStatePoolMap(ExplosionObjectState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief ステートプール用マップをクリアする
*/
void ExplosionObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
}
