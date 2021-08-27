#pragma once
#include "Component.h"
#include <string>
#include <vector>

class CubeMapComponent :
    public Component
{
public:

	CubeMapComponent(class GameObject* _owner);
	~CubeMapComponent();

	void CreateTexture(const std::string& in_filePath);

	void Draw(class Shader* in_shader);

	class Texture* GetSkyBoxTexture() { return texture; }


	void SetIsVisible(bool in_visible) { isVisible = in_visible; }         // キューブを表示するかしないかのセット
	void SetLuminance(float in_luminance) { luminance = in_luminance; }    // 輝度情報のセット


private:

	class Texture* texture;

	float luminance;               // 輝度情報

	bool isVisible;                // 描画するかしないかのフラグ

};

