//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectBase.h"
#include "CameraObjectStateBase.h"

/*
@fn コンストラクタ
@param	再利用するかフラグ
@param	ObjectTag
*/
CameraObjectBase::CameraObjectBase(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, DeltaCorrection(8.0f)
	, offSetPosition(Vector3(Vector3::Zero))
{
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CameraObjectBase::~CameraObjectBase()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CameraObjectBase::UpdateGameObject(float _deltaTime)
{
}

/*
@fn 入力関数
@brief	入力処理を行う
@param	_keyState 入力情報
*/
void CameraObjectBase::GameObjectInput(const InputState& _keyState)
{
}

/*
@brief ステートプール用マップにステートクラスを追加する関数
@param	_state 追加するステートクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void CameraObjectBase::AddStatePoolMap(CameraObjectStateBase* _state, CameraState _stateTag)
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
void CameraObjectBase::RemoveStatePoolMap(CameraState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief ステートプール用マップをクリアする
*/
void CameraObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
}
