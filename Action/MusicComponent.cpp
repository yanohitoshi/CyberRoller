//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MusicComponent.h"
#include "AudioResourceManager.h"
#include "Music.h"

/*
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	読み込むサウンドファイルのパス
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
MusicComponent::MusicComponent(GameObject* _owner, const std::string& _fileName, int _updateOrder)
	: AudioComponent(_owner, _fileName, _updateOrder)
{
	// リソース管理クラスにファイルネームを渡しロードしてもらったものをもらう
	myMusic = AUDIO_RESOURCE->AddMusic(_fileName);
}

/*
@fn デストラクタ
@brief  componentの削除を行う
*/
MusicComponent::~MusicComponent()
{
	// リソースの削除を管理者ファイルネームを渡し行う
	AUDIO_RESOURCE->RemoveMusic(myFileName);
}

/*
@fn フェードイン再生関数(ミュージック)
@brief ミュージックのフェードイン再生を行う
@param fadeInTime　フェードインにかける時間
*/
void MusicComponent::PlayFadeIn(int _fadeInTime)
{
	myMusic->FadeInMusic(_fadeInTime);
}

/*
@fn 再生関数(ミュージック)
@brief ミュージックを再生を行う
*/
void MusicComponent::Play()
{
	myMusic->Play();
}

/*
@fn フェードアウト関数(ミュージック)
@brief 再生中のミュージックのフェードアウトを行う
@param fadeOutTime　フェードアウトにかける時間
*/
void MusicComponent::FadeOut(int _fadeOutTime)
{
	myMusic->FadeOutMusic(_fadeOutTime);
}

/*
@fn 停止関数(ミュージック)
@brief ミュージックを停止を行う
*/
void MusicComponent::Stop()
{
	myMusic->Stop();
}

/*
@fn 再生状態確認関数(ミュージック)
@brief ミュージックが再生中かどうかフラグの取得
@return bool true 再生中 : false 非再生中
*/
bool MusicComponent::IsPlaying()
{
	return myMusic->IsPlaying();
}