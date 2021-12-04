#include "TitleSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"

TitleSceneSoundManager::TitleSceneSoundManager()
	: GameObject(false,Tag::AUDIO)
{
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Cyber01.wav");
}

TitleSceneSoundManager::~TitleSceneSoundManager()
{
}

void TitleSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	if (!bgm->IsPlaying())
	{
		bgm->Play();
	}
}
