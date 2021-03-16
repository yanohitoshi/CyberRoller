#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <SDL_mixer.h>
#include <iostream>

// 未実装
class Sound
{
public:
    Sound();
    ~Sound();
    void          Play();       // 再生
    void          Stop();       // ストップ
    bool          LoadSound(const std::string& fileName); // サウンドファイル読み込み
    /*
    @fn 再生中か
    */
    bool IsPlaying();  // 現在再生中か？

private:

    // サウンドデータ
    Mix_Chunk* mChunk;
    // 再生チャンネル
    int mChannel;

};

