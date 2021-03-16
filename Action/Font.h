#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <string>
#include <unordered_map>
#include "SDL_ttf.h"
#include "Math.h"
#include "RapidJsonHelper.h"

/*
@file Font.h
@brief �t�H���g�f�[�^�̃��[�h�ƃt�H���g�̐������s��
*/

class Font
{
public:
	
	/*
	@fn �R���X�g���N�^
	@brief Font�N���X�̐������s��
	*/
	Font();
	
	/*
	@fn �f�X�g���N�^
	@brief Font�N���X�̍폜���s��
	*/
	~Font();

	/*
	@fn �t�@�C�����[�h�֐�
	@brief TTF�t�@�C���̃��[�h���s��
	@param fileName ���[�h����t�@�C���̃p�X
	*/
	bool Load(const std::string& fileName);

	/*
	@fn �A�����[�h�֐�
	@brief TTF�t�@�C���̃A�����[�h���s��
	*/
	void Unload();

	/*
	@fn texture�����֐�
	@brief �t�H���g���g�p����texture�̐������s��
	@param renderingText ��������texture�Ɏg�p���镶����
	@param color �w�肷��F�i�f�t�H���g�͔��j
	@param pointSize �t�H���g�̃T�C�Y�i�f�t�H���g��30�j
	*/
	class Texture* RenderText(const std::string& renderingText,const Vector3& color = Color::White,int pointSize = 30);

private:

	// �|�C���g�T�C�Y�̃t�H���g�f�[�^�ւ̃}�b�v
	std::unordered_map<int, TTF_Font*> mFontData;
};

