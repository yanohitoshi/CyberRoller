
/*–¢ŽÀ‘•‚È‚Ì‚ÅŽg—p‚µ‚Ä‚¢‚Ü‚¹‚ñ*/

#include "Music.h"
Music::Music()
	:music(nullptr)
{
}

Music::~Music()
{
	Mix_FreeMusic(music);
}

void Music::Play()
{
	Mix_PlayMusic(music, -1);
}

void Music::FadeInMusic(int fadeInTime)
{
	Mix_FadeInMusic(music, -1, fadeInTime);
}

bool Music::LoadMusic(const std::string& fileName)
{
	music = Mix_LoadMUS(fileName.c_str());
	return music != nullptr;
}

void Music::Stop()
{
	Mix_HaltMusic();
}

void Music::FadeOutMusic(int fadeOutTime)
{
	Mix_FadeOutMusic(fadeOutTime);
}

bool Music::IsPlaying()
{
	return Mix_PlayingMusic();
}
