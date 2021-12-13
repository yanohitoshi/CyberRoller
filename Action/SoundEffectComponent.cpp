//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SoundEffectComponent.h"
#include "AudioResourceManager.h"
#include "Sound.h"

/*
@fn コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	サウンドのファイルパス
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
SoundEffectComponent::SoundEffectComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: AudioComponent(_owner, _fileName ,_updateOrder)
{
	// リソース管理クラスにファイルネームを渡しロードしてもらったものをもらう
	mySound = AUDIO_RESOURCE->AddSound(_fileName);
}

/*
@fn デストラクタ
@brief  componentの削除を行う
*/
SoundEffectComponent::~SoundEffectComponent()
{
	// リソースの削除を管理者ファイルネームを渡し行う
	AUDIO_RESOURCE->RemoveSound(myFileName);

	if (mySound != nullptr)
	{
		mySound = nullptr;
	}
}

/*
@fn 再生関数(サウンド)
@brief サウンドの再生を行う
*/
void SoundEffectComponent::Play()
{
	mySound->Play();
}

/*
@fn 停止関数(サウンド)
@brief サウンドの停止を行う
*/
void SoundEffectComponent::Stop()
{
	mySound->Stop();
}

/*
@fn 再生状態確認関数(サウンド)
@brief 指定したサウンドが再生中かどうかフラグの取得
@return bool true 再生中 : false 非再生中
*/
bool SoundEffectComponent::IsPlaying()
{

	return 	mySound->IsPlaying();
}

void SoundEffectComponent::SetVolume(int _volume)
{
	mySound->SetChannelVolume(_volume);
}