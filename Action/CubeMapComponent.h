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


	void SetIsVisible(bool in_visible) { isVisible = in_visible; }         // �L���[�u��\�����邩���Ȃ����̃Z�b�g
	void SetLuminance(float in_luminance) { luminance = in_luminance; }    // �P�x���̃Z�b�g


private:

	class Texture* texture;

	float luminance;               // �P�x���

	bool isVisible;                // �`�悷�邩���Ȃ����̃t���O

};

