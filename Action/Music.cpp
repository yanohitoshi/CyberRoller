//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Music.h"

/*
@fn コンストラクタ
@brief ミュージッククラスの生成を行う
*/
Music::Music()
	:music(nullptr)
{
}

/*
@fn デストラクタ
@brief ミュージックの解放を行う
*/
Music::~Music()
{
	Mix_FreeMusic(music);
}

/*
@fn 再生関数
@brief ミュージックを再生を行う
*/
void Music::Play()
{
	Mix_PlayMusic(music, -1);
}

/*
@fn フェードイン関数
@brief ミュージックのフェードインを行う
*/
void Music::FadeInMusic(int fadeInTime)
{
	Mix_FadeInMusic(music, -1, fadeInTime);
}

/*
@fn 再生関数
@brief ミュージック読み込みを行う
@param fileName　読み込むミュージックファイルのパス
@return bool true 読み込み成功 : false 読み込み失敗
*/
bool Music::LoadMusic(const std::string& fileName)
{
	music = Mix_LoadMUS(fileName.c_str());
	return music != nullptr;
}

/*
@fn 停止関数
@brief ミュージックを停止する
*/
void Music::Stop()
{
	Mix_HaltMusic();
}

/*
@fn フェードアウト関数
@brief 再生中のミュージックをフェードアウトする
*/
void Music::FadeOutMusic(int fadeOutTime)
{
	Mix_FadeOutMusic(fadeOutTime);
}

/*
@fn 再生状態確認関数
@brief ミュージックが再生中かどうかフラグの取得
@return bool true 再生中 : false 非再生中
*/
bool Music::IsPlaying()
{
	return Mix_PlayingMusic();
}
