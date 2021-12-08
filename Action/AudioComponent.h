#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include <String>

/*
@file AudioComponent.h
@brief Componentクラスを継承したオーディオ関連Componentクラスの基底のクラス
*/
class AudioComponent :
    public Component
{
public:

	/*
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	読み込むサウンドファイルのパス
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	*/
	AudioComponent(GameObject* _owner, const std::string& _fileName,int _updateOrder = 200);

	/*
	@brief	デストラクタ
	*/
	~AudioComponent()override {};

protected:

	// 自分のサウンドのファイルネーム
	std::string myFileName;

public: // ゲッターセッター

	/*
	@fn 自分のファイルネームのgetter
	@return 自分のファイルネームを返す
	*/
	const std::string& GetFileName() { return myFileName; }

};