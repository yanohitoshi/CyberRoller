#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class Mesh;
class GeometryInstanceComponent;
/*
@file LightObject.h
@brief ライトオブジェクト(置物)の生成と更新処理を行う
*/
class LightObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	@param	右側に添わせるかどうか
	*/
	LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,bool _isRight);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~LightObject()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 3Dモデルの描画を行うクラス
	Mesh* mesh;
	GeometryInstanceComponent* geometryInstanceComponent;
	// X軸のずらす定数値
	const float ShiftPositionX;
	// 右側に添わせる場合のY軸をずらす定数値
	const float ShiftRightPositionY;
	// 右側に添わせる場合のY軸をずらす定数値
	const float ShiftLeftPositionY;
	// Z軸のずらす定数値
	const float ShiftPositionZ;

};

