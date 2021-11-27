#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MeshComponent.h"
#include "MatrixPalette.h"

/*
@file SkeletalMeshComponent.h
@brief �X�P���g���f�[�^�̕`��ƃA�j���[�V����
*/
class SkeletalMeshComponent : public MeshComponent
{
public:
	
	/*
	@fn �R���X�g���N�^
	@param _owner �e�ƂȂ�GameObject�̃|�C���^
	*/
	SkeletalMeshComponent(class GameObject* owner);

	/*
	@brief�@�X�V����
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime) override;

	/*
	@brief�@�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* shader) override;

   	/*
	@fn �A�j���[�V�����̍Đ�
	@param _anim �A�j���[�V�����f�[�^�N���X
	@param _playRate �A�j���[�V�����̍Đ����x
	@return �A�j���[�V�����̎c�莞��
	*/
	float PlayAnimation(const class Animation* _anim, float _playRate = 1.0f);

	/*
	@fn �A�j���[�V�������Đ��������ׂ�֐�
	*/
	bool IsPlaying();

protected:

	/*
	@fn �s��p���b�g�̌v�Z
	*/
	void ComputeMatrixPalette();                                       
	// �s��p���b�g
	MatrixPalette palette;                                    
	// �X�P���g���f�[�^
	const class Skeleton* skeleton;                                       
	// �A�j���[�V�����f�[�^
	const class Animation* animation;                                     
	// �A�j���[�V�����̍Đ����x
	float animPlayRate;                                                  
	// �A�j���[�V��������
	float animTime;                                                       
	//�X�P���g���f�[�^�ɏ�Z����F
	Vector3 color;
	// �P�x
	float luminance;

	/*
	@fn texture�Z�b�g�p�֐�
	@param _shader �Z�b�g����V�F�[�_�[�̃|�C���^
	*/
	void SetTextureToShader(Shader* _shader);

public: //�Q�b�^�[�Z�b�^�[

	/*
	@param _skeleton �X�P���g���f�[�^
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { skeleton = _skeleton; }
	/*
	@param _color �X�P���g���f�[�^�ɏ�Z����F
	*/
	void SetColor(const Vector3& _color) { color = _color; }

	/*
	@param _color �X�P���g���f�[�^�ɏ�Z����F
	*/
	void SetAnimPlayRate(const float _animPlayRate) { animPlayRate = _animPlayRate; }
};