//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "AudioComponent.h"
#include "GameObject.h"

/*
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	読み込むサウンドファイルのパス
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
AudioComponent::AudioComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: Component(_owner, _updateOrder)
	, myFileName(_fileName)
{
}