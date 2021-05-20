#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"

// クラスの前方宣言
class GameObject;
class Shader;
class Texture;

/*
@file SpriteComponent.h
@brief 画像データクラスを管理し、スクリーン上に描画するクラス
*/
class SpriteComponent : public Component
{
public:
	
	/*
	@fn コンストラクタ
	@param _owner 親となるGameObjectのポインタ
	@param _isBackGround 背景画像かどうかのフラグ(bool)
	@param _drawOrder 描画順を決める値(int)
	*/
    SpriteComponent(GameObject* _owner,bool _isBackGround, int _drawOrder = 100);

	/*
	@fn デストラクタ
	@brief  Componentの削除を行う
	*/
    ~SpriteComponent();

	/*
	@brief	描画処理
	@param _shader 使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* _shader);

protected:

	//クラスのポインタ
    Texture* texture;
	//描画される順番（数値が少ないほど早く更新される）
    int drawOrder;
	//テクスチャの横幅
    int textureWidth;
	//テクスチャの縦幅
    int textureHeight;
	//描画を行うか
	bool visible;

	bool isBackGround;
	float alpha;

public://ゲッターセッター

	/*
	@fn テクスチャをセットし縦横の長さを計算する
	@param _texture 使用するテクスチャのポインタ
	*/
	virtual void SetTexture(Texture* _texture);

	/*
	@return テクスチャの横幅
	*/
	int GetTexWidth() const { return textureWidth; }

	/*
	@return テクスチャの縦幅
	*/
	int GetTexHeight() const { return textureHeight; }

	/*
	@return 描画順
	*/
	int GetDrawOrder() { return drawOrder; }

	/*
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/*
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return visible; }

	/*
	@brief　背景画像かどうかを取得する
	@return	true : 背景 , false : 背景じゃない
	*/
	bool GetIsBackGround()const { return isBackGround; }

	/*
	@brief　Alpha値の値を設定する
	@return	_alpha 設定するAlpha値の値(float)
	*/
	void SetAlpha(float _alpha) { alpha = _alpha; }
	
	/*
	@brief　Alpha値の値を取得する
	@return	設定されているAlpha値の値(float)
	*/
	float GetAlpha() const { return alpha; }

};

