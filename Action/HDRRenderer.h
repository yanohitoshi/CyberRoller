#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <vector>
#include <unordered_map>
#include "Math.h"

/*
@file HDRRenderer.h
@brief HDR�E�u���[���`��̐i�s���s��
*/
class HDRRenderer
{
public:
	
	/*
	@fn �R���X�g���N�^
	@brief  HDRRenderer�̐������s��
	@param	fboWidth FBO�̕�
	@param	fboHeight FBO�̍���
	@param	bloomLevel �u���[���̃��x��
	*/
	HDRRenderer(int fboWidth,int fboHeight,int bloomLevel);

	/*
	@fn �f�X�g���N�^
	@brief HDRRenderer�̍폜���s��
	*/
	~HDRRenderer();

	/*
	@fn HDR�̃��R�[�f�B���O�J�n�֐�
	@brief �`��Ώۂ�HdrFBO�ɕύX���J���[�o�b�t�@���N���A����
	*/
	void HdrRecordBegin();
	
	/*
	@fn HDR�̃��R�[�f�B���O�����I���֐�
	@brief �`��Ώۂ��X�N���[���ɖ߂�
	*/
	void HdrRecordEnd();
	
	/*
	@fn HiBrightBlur�����֐�
	@brief �_�E���T���v�����O�ƃK�E�X�ڂ������s��
	*/
	void HiBrightBlurCreate();
	
	/*
	@fn �g�[���}�b�v�ƃu���C�g�u���[�̍����֐�
	@brief ���摜��BrightBlur�摜����������
	*/
	void HdrTonemapAndBrightBlurCombine();

	/*
	@fn �[�x���̃R�s�[�֐�
	@brief �K�E�X�o�b�t�@�̐[�x�����X�N���[���̐[�x�o�b�t�@�ɃR�s�[����
	*/
	void CopyDepthToScreen();

	/*
	@fn ColorTexureID��getter
	@return unsigned int hdrColorBuffers[0]
	*/
	unsigned int GetColorTexID() { return hdrColorBuffers[0]; }
	
	/*
	@fn ColorTexureID��getter
	@return unsigned int hdrColorBuffers[1]
	*/
	unsigned int GetHDRTexID() { return hdrColorBuffers[1]; }

private:
	
	/*
	@fn HDRBuffer�̏������֐�
	@brief ���������_ColorBuffer������������
	*/
	void  InitHDRBuffers();

	/*
	@fn BlurBuffer�̏������֐�
	@brief blurFBOs��blurBufferTexs������������
	*/
	void  InitBlurBuffers();

	/*
	@fn ScreenQuadVAO�̏������֐�
	@brief �X�N���[���S�̂�`�悷��l�p�`������������
	*/
	void  InitScreenQuadVAO();

	float GaussianDistribution(const Vector2& pos, float rho);
	void  CalcGaussBlurParam(int w, int h, Vector2 dir, float deviation);

	// HDR�Ɏg�p����Shader�̃|�C���^�ϐ�
	class Shader* gaussianBlurShader;
	class Shader* downSamplingShader;
	class Shader* hdrToneAndBlurBlendShader;

	// �X�N���[���S�̂�`�悷��l�p�`�pVAO��VBO
	unsigned int quadScreenVAO;
	unsigned int quadScreenVBO;

	// buffer�̕��ƍ����ϐ�
	unsigned int bufferWidth;
	unsigned int bufferHeight;

	// bloomBuffer�̃��x���ݒ�p�ϐ�
	unsigned int bloomBufferLevel;
	// bloomBuffer�̃i���o�����O�p�ϐ�
	unsigned int bloomBufferNum;
	
	// ���������_FBO
	unsigned int hdrFBO;
	// ���������_RBO
	unsigned int hdrRBO;
	// ���������_ColorBuffer
	unsigned int hdrColorBuffers[2];

	// �K�E�X�ڂ����̃T���v�����O�_
	const int sampleCount;

	// �u���[�p�̃t���[���o�b�t�@�I�u�W�F�N�g
	std::vector<unsigned int> blurFBOs;
	// �u���[���ʂ̃e�N�X�`��ID
	std::vector<unsigned int> blurBufferTexs;

	// �T���v�����O�_�̍��W(u,v) & w:�d��
	Vector3 offset[15];

};

