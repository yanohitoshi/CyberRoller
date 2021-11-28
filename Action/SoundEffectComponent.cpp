#include "SoundEffectComponent.h"
#include "AudioResourceManager.h"
#include "Sound.h"

SoundEffectComponent::SoundEffectComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: AudioComponent(_owner, _fileName ,_updateOrder)
{
	mySound = AUDIO_RESOURCE->AddSound(_fileName);
}

SoundEffectComponent::~SoundEffectComponent()
{
	AUDIO_RESOURCE->RemoveSound(myFileName);
}

void SoundEffectComponent::Play()
{
	mySound->Play();
}

void SoundEffectComponent::Stop()
{
	mySound->Stop();
}

bool SoundEffectComponent::IsPlaying()
{

	return 	mySound->IsPlaying();
}
