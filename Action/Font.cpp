//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Font.h"
#include "Texture.h"
#include <vector>
#include "Game.h"
#include "RenderingObjectManager.h"

/*
@fn �R���X�g���N�^
@brief Font�N���X�̐������s��
*/
Font::Font()
{
}

/*
@fn �f�X�g���N�^
@brief Font�N���X�̍폜���s��
*/
Font::~Font()
{
}

/*
@fn �t�@�C�����[�h�֐�
@brief TTF�t�@�C���̃��[�h���s��
@param fileName ���[�h����t�@�C���̃p�X
*/
bool Font::Load(const std::string& fileName)
{
	// �T�|�[�g����Ă���t�H���g�T�C�Y
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		fontData.emplace(size, font);
	}
	return true;
}

/*
@fn �A�����[�h�֐�
@brief TTF�t�@�C���̃A�����[�h���s��
*/
void Font::Unload()
{
	for (auto& font : fontData)
	{
		TTF_CloseFont(font.second);
	}
}

/*
@fn texture�����֐�
@brief �t�H���g���g�p����texture�̐������s��
@param renderingText ��������texture�Ɏg�p���镶����
@param color �w�肷��F�i�f�t�H���g�͔��j
@param pointSize �t�H���g�̃T�C�Y�i�f�t�H���g��30�j
*/
Texture* Font::RenderText(const std::string& renderingText,const Vector3& color,int pointSize)
{
	//return nullptr;
	Texture* texture = nullptr;

	// SDL_Color��ϊ�
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	// �t�H���g�f�[�^����|�C���g�T�C�Y��T��
	auto iter = fontData.find(pointSize);
	if (iter != fontData.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = renderingText;

		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// �T�[�t�F�X����e�N�X�`���ɕϊ�����
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return texture;
}

