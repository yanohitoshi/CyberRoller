#include "MusicComponent.h"
#include "AudioResourceManager.h"
#include "Music.h"

MusicComponent::MusicComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: AudioComponent(_owner, _fileName, _updateOrder)
{
	myMusic = AUDIO_RESOURCE->AddMusic(_fileName);
}

MusicComponent::~MusicComponent()
{
	AUDIO_RESOURCE->RemoveMusic(myFileName);
}

void MusicComponent::PlayFadeIn(int fadeInTime)
{
	myMusic->FadeInMusic(fadeInTime);
}

void MusicComponent::Play()
{
	myMusic->Play();
}

void MusicComponent::FadeOut(int fadeOutTime)
{
	myMusic->FadeOutMusic(fadeOutTime);
}

void MusicComponent::Stop()
{
	myMusic->Stop();
}

bool MusicComponent::IsPlaying()
{
	return myMusic->IsPlaying();
}