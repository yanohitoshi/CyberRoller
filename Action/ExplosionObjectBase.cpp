#include "ExplosionObjectBase.h"
#include "ExplosionObjectStateBase.h"

ExplosionObjectBase::ExplosionObjectBase(const Tag _objectTag)
	: GameObject(false, _objectTag)
	, hitPosition(Vector3::Zero)
	, firstPosition(Vector3::Zero)
	, fallArea(Vector3::Zero)
	, fallSpeed(0.0f)
{
}

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

void ExplosionObjectBase::RemoveStatePoolMap(ExplosionObjectState _stateTag)
{
	delete statePoolMap[_stateTag];
}

void ExplosionObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
}
