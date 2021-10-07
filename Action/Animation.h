#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------

#include "Math.h"
#include "BoneTransform.h"
#include <vector>
#include <string>

/*
 @file Animation.h
 @fn Skeleton��p�����A�j���[�V�����̃f�[�^�N���X
*/
class Animation
{
public:

	/*
	@fn �A�j���[�V�����ǂݍ���
	@param �A�j���[�V�����ւ̃p�X
	*/
	bool Load(const std::string& fileName,bool _loop);

private:

	//�A�j���[�V�����̂��߂̃{�[����
	size_t numBones;
	//�A�j���[�V�����̃t���[����
	size_t numFrames;
	//�A�j���[�V�����̍Đ�����
	float duration;
	//�A�j���[�V�����̃t���[���Ԃ̎���
	float frameDuration;
	// ���[�v�A�j���[�V�������邩�H
	bool isLoopAnimation;

	/*
	 �g���b�N��̊e�t���[���̕ϊ����B
	 �O���̃x�N�g���̊e�C���f�b�N�X�̓{�[���A
	 �����̃x�N�g���̓t���[���B�@�@�@�@�@�@�@
	 mTracks[�{�[��][�t���[����]
	*/
	std::vector<std::vector<BoneTransform>> tracks;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@fn �{�[����
	*/
	size_t GetNumBones() const { return numBones; }

	/*
	@fn �t���[����
	*/
	size_t GetNumFrames() const { return numFrames; }

	/*
	@fn �A�j���[�V��������
	*/
	float GetDuration() const { return duration; }

	/*
	@fn �t���[������
	*/
	float GetFrameDuration() const { return frameDuration; }

	/*
	@fn	inTime�������_�̃O���[�o���|�[�Y�z��̎擾
	@param	_outPoses outPoses�̉ϒ��z��(Matrix4)
	@param	_inSkeleton �X�P���g���f�[�^�̃|�C���^
	@param	_inTime
	*/
	void GetGlobalPoseAtTime(std::vector<Matrix4>& _outPoses, const class Skeleton* _inSkeleton, float _inTime) const;

	/*
	@fn	���[�v����A�j���[�V�������ǂ����̃t���O�̎擾
	@return	isLoopAnimation outPoses�̉ϒ��z��(Matrix4)
	*/
	bool IsLoopAnimation() const { return isLoopAnimation; }

};
