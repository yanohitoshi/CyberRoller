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
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = statePoolMap.find(_stateTag);

	//����Ƃ�
	if (stateMaps != statePoolMap.end())
	{
		return;
	}
	else //�Ȃ��Ƃ�
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
