#pragma once

/*
@file FPS.h
@brief 1�t���[���ɂ����������Ԃ��v���������݂���N���X
*/
class FPS
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	FPS();

	/*
	@fn �f�X�g���N�^
	*/
	~FPS();

	/*
	@brief	�t���[�����̏���
	*/
	void Update();

private:

	/*
	@brief	FPS���ݒ�l���傫���Ȃ�Ȃ����߂̐���
	*/
	void Wait();
	//�t���[�����[�g�̍ō��l
	const Uint32 setFps;				
	//�P�t���[���ɂ����鎞��
	const Uint32 oneFrameTickCount;		
	//�t���[���̃J�E���^�[
	Uint32 fpsCount;					
	//FPS�̌v�Z���n�߂����̎���
	Uint32 frameStartTickTime;			
	//�v�Z�����t���[�����[�g
	Uint32 fps;							
	//�O�̃t���[���̂�����������
	int beforetickCount;				
	//���݂̃t���[���̂�����������
	float deltaTime;

public:

	//�Q�b�^�[�Z�b�^�[
	/*
	@fn �f���^�^�C����getter�֐�
	@brief ���݂̃t���[���ɂ����������Ԃ��擾
	@return ���݂̃t���[���ɂ�����������
	*/
	float GetDeltaTime() const { return deltaTime; }
};

