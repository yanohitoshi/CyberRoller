#include "FirstSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "SoundEffectComponent.h"
#include "BaseScene.h"

FirstSceneSoundManager::FirstSceneSoundManager(BaseScene* _owner)
	: GameObject(false, Tag::AUDIO)
{
	owner = _owner;
	isCountDownPlay = true;
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Cyber02.wav");
	countDown = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/CountDown/CountDown.wav");
}

FirstSceneSoundManager::~FirstSceneSoundManager()
{
}

void FirstSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	if (!bgm->IsPlaying() && !isCountDownPlay)
	{
		bgm->Play();
	}

	if (!owner->GetStartScene() && isCountDownPlay)
	{
		countDown->Play();
		isCountDownPlay = false;
	}
}