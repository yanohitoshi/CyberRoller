//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "AudioComponent.h"
#include "GameObject.h"

AudioComponent::AudioComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: Component(_owner, _updateOrder)
	, myFileName(_fileName)
{
}