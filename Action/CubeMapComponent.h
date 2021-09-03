#pragma once
#include "Component.h"
#include <string>
#include <vector>

/*
 @file CubeMapComponent.h
 @brief キューブマップの管理と描画を行う
*/
class CubeMapComponent :
    public Component
{
public:

	/*
	@fn コンストラクタ
	@param _owner 親クラスのポインタ
	*/
	CubeMapComponent(class GameObject* _owner);

	/*
	@fn デストラクタ
	@brief  Componentの削除を行う
	*/
	~CubeMapComponent();

	/*
	@brief　texture生成処理
	@param	in_filePath 使用するtextureのファイルパス
	*/
	void CreateTexture(const std::string& in_filePath);

	/*
	@brief　描画処理
	@param	in_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* in_shader);

	/*
	@brief　スカイボックスに使用しているtextureのgetter
	@param	texture 使用しているtextureクラスのポインタ
	*/
	class Texture* GetSkyBoxTexture() { return texture; }

	// キューブを表示するかしないかのセット
	void SetIsVisible(bool in_visible) { isVisible = in_visible; }

	// 輝度情報のセット
	void SetLuminance(float in_luminance) { luminance = in_luminance; }


private:

	// textureクラスのポインタ
	class Texture* texture;

	// 輝度情報
	float luminance;

	// 描画するかしないかのフラグ
	bool isVisible;

};

