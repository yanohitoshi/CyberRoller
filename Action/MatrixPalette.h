#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Math.h"

const size_t MaxSkeletonBones = 196;

struct MatrixPalette
{
	Matrix4 mEntry[MaxSkeletonBones];
};
