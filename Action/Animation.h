#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------

#include "Math.h"
#include "BoneTransform.h"
#include <vector>
#include <string>

/*
 @file Animation.h
 @fn Skeletonを用いたアニメーションのデータクラス
*/
class Animation
{
public:

	/*
	@fn アニメーション読み込み
	@param アニメーションへのパス
	*/
	bool Load(const std::string& fileName,bool _loop);

private:

	//アニメーションのためのボーン数
	size_t numBones;
	//アニメーションのフレーム数
	size_t numFrames;
	//アニメーションの再生時間
	float duration;
	//アニメーションのフレーム間の時刻
	float frameDuration;
	// ループアニメーションするか？
	bool isLoopAnimation;

	/*
	 トラック上の各フレームの変換情報。
	 外側のベクトルの各インデックスはボーン、
	 内側のベクトルはフレーム。　　　　　　　
	 mTracks[ボーン][フレーム数]
	*/
	std::vector<std::vector<BoneTransform>> tracks;

public: //ゲッターセッター

	/*
	@fn ボーン数
	*/
	size_t GetNumBones() const { return numBones; }

	/*
	@fn フレーム数
	*/
	size_t GetNumFrames() const { return numFrames; }

	/*
	@fn アニメーション期間
	*/
	float GetDuration() const { return duration; }

	/*
	@fn フレーム期間
	*/
	float GetFrameDuration() const { return frameDuration; }

	/*
	@fn	inTime時刻時点のグローバルポーズ配列の取得
	@param	_outPoses outPosesの可変長配列(Matrix4)
	@param	_inSkeleton スケルトンデータのポインタ
	@param	_inTime
	*/
	void GetGlobalPoseAtTime(std::vector<Matrix4>& _outPoses, const class Skeleton* _inSkeleton, float _inTime) const;

	/*
	@fn	ループするアニメーションかどうかのフラグの取得
	@return	isLoopAnimation outPosesの可変長配列(Matrix4)
	*/
	bool IsLoopAnimation() const { return isLoopAnimation; }

};
