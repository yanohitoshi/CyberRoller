#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <vector>
#include <unordered_map>
#include "Math.h"

/*
@file HDRRenderer.h
@brief HDR・ブルーム描画の進行を行う
*/
class HDRRenderer
{
public:
	
	/*
	@fn コンストラクタ
	@brief  HDRRendererの生成を行う
	@param	fboWidth FBOの幅
	@param	fboHeight FBOの高さ
	@param	bloomLevel ブルームのレベル
	*/
	HDRRenderer(int fboWidth,int fboHeight,int bloomLevel);

	/*
	@fn デストラクタ
	@brief HDRRendererの削除を行う
	*/
	~HDRRenderer();

	/*
	@fn HDRのレコーディング開始関数
	@brief 描画対象をHdrFBOに変更しカラーバッファをクリアする
	*/
	void HdrRecordBegin();
	
	/*
	@fn HDRのレコーディング準備終了関数
	@brief 描画対象をスクリーンに戻す
	*/
	void HdrRecordEnd();
	
	/*
	@fn HiBrightBlur生成関数
	@brief ダウンサンプリングとガウスぼかしを行う
	*/
	void HiBrightBlurCreate();
	
	/*
	@fn トーンマップとブライトブルーの合成関数
	@brief 元画像とBrightBlur画像を合成する
	*/
	void HdrTonemapAndBrightBlurCombine();

	/*
	@fn 深度情報のコピー関数
	@brief ガウスバッファの深度情報をスクリーンの深度バッファにコピーする
	*/
	void CopyDepthToScreen();

	/*
	@fn ColorTexureIDのgetter
	@return unsigned int hdrColorBuffers[0]
	*/
	unsigned int GetColorTexID() { return hdrColorBuffers[0]; }
	
	/*
	@fn ColorTexureIDのgetter
	@return unsigned int hdrColorBuffers[1]
	*/
	unsigned int GetHDRTexID() { return hdrColorBuffers[1]; }

private:
	
	/*
	@fn HDRBufferの初期化関数
	@brief 浮動小数点ColorBufferを初期化する
	*/
	void  InitHDRBuffers();

	/*
	@fn BlurBufferの初期化関数
	@brief blurFBOsとblurBufferTexsを初期化する
	*/
	void  InitBlurBuffers();

	/*
	@fn ScreenQuadVAOの初期化関数
	@brief スクリーン全体を描画する四角形を初期化する
	*/
	void  InitScreenQuadVAO();

	float GaussianDistribution(const Vector2& pos, float rho);
	void  CalcGaussBlurParam(int w, int h, Vector2 dir, float deviation);

	// HDRに使用するShaderのポインタ変数
	class Shader* gaussianBlurShader;
	class Shader* downSamplingShader;
	class Shader* hdrToneAndBlurBlendShader;

	// スクリーン全体を描画する四角形用VAOとVBO
	unsigned int quadScreenVAO;
	unsigned int quadScreenVBO;

	// bufferの幅と高さ変数
	unsigned int bufferWidth;
	unsigned int bufferHeight;

	// bloomBufferのレベル設定用変数
	unsigned int bloomBufferLevel;
	// bloomBufferのナンバリング用変数
	unsigned int bloomBufferNum;
	
	// 浮動小数点FBO
	unsigned int hdrFBO;
	// 浮動小数点RBO
	unsigned int hdrRBO;
	// 浮動小数点ColorBuffer
	unsigned int hdrColorBuffers[2];

	// ガウスぼかしのサンプリング点
	const int sampleCount;

	// ブラー用のフレームバッファオブジェクト
	std::vector<unsigned int> blurFBOs;
	// ブラー結果のテクスチャID
	std::vector<unsigned int> blurBufferTexs;

	// サンプリング点の座標(u,v) & w:重み
	Vector3 offset[15];

};

