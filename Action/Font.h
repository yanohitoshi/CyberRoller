#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <string>
#include <unordered_map>
#include "SDL_ttf.h"
#include "Math.h"
#include "RapidJsonHelper.h"

/*
@file Font.h
@brief フォントデータのロードとフォントの生成を行う
*/

class Font
{
public:
	
	/*
	@fn コンストラクタ
	@brief Fontクラスの生成を行う
	*/
	Font();
	
	/*
	@fn デストラクタ
	@brief Fontクラスの削除を行う
	*/
	~Font();

	/*
	@fn ファイルロード関数
	@brief TTFファイルのロードを行う
	@param fileName ロードするファイルのパス
	*/
	bool Load(const std::string& fileName);

	/*
	@fn アンロード関数
	@brief TTFファイルのアンロードを行う
	*/
	void Unload();

	/*
	@fn texture生成関数
	@brief フォントを使用したtextureの生成を行う
	@param renderingText 生成するtextureに使用する文字列
	@param color 指定する色（デフォルトは白）
	@param pointSize フォントのサイズ（デフォルトは30）
	*/
	class Texture* RenderText(const std::string& renderingText,const Vector3& color = Color::White,int pointSize = 30);

private:

	// ポイントサイズのフォントデータへのマップ
	std::unordered_map<int, TTF_Font*> mFontData;
};

