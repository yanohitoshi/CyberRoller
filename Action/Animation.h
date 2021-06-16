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
	mTracks[ボーン][フレーム数]*/
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

	//指定された配列を、アニメーションの指定された時間に、
	//各ボーンのグローバル（現在の）ポーズマトリックスで埋める。
	//時間は > = 0.0fかつ <= 期間であると予想される
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

	//ループするアニメーションかどうかのフラグをとる
	bool IsLoopAnimation() const { return isLoopAnimation; }

};
